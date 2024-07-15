#pragma once

#include"MemoryManager.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
	template<typename T, std::size_t MAX_OBJECT_PER_CHUNK>
	class MemoryChunkManager : public MemoryManager {
		static constexpr size_t MEMORY_CHUNK_MAX_SIZE = sizeof(T) * MAX_OBJECT_PER_CHUNK;
	
		using ObjectList = std::list<T*>;

		class MemoryChunk {
		public:
			MemoryChunk(PoolAllocator* allocator) : mAllocator(allocator) {
			}

			void* Allocate() {
				void* memory = mAllocator->Allocate();

				VI_ASSERT(memory && "Failed to allocate memory");

				mObjects.emplace_back((T*)memory);
				return memory;
			}

			void Free(void* memory) {
				mAllocator->Free(memory);
				auto iter = std::find(mObjects.begin(), mObjects.end(), memory);
				if (iter != mObjects.end()) {
					mObjects.erase(iter);
				}
			}

			bool HasSlot() {
				return mObjects.size() < MAX_OBJECT_PER_CHUNK;
			}

			bool Contains(void* memory) {
				return mAllocator->Contains(memory);
			}

			const ObjectList& GetObjects() const { return mObjects; }
			
			void Clear() {
				mAllocator->Clear();
				mObjects.clear();
			}

			void* GetStartAddress() const { return mAllocator->GetStartAddress(); }

		private:
			PoolAllocator* mAllocator;
			ObjectList mObjects;
		};

		using MemoryChunkList = std::list<MemoryChunk*>;

		class Iterator {
		public:
			Iterator(typename MemoryChunkList::iterator begin, typename MemoryChunkList::iterator end) : mCurrentChunk(begin), mEndChunk(end) {
				if (begin != end) {
					VI_ASSERT(*mCurrentChunk && "Invalid memory chunk");
					mCurrentObject = (*mCurrentChunk)->GetObjects().begin();
				}
				else {
					mCurrentObject = (*std::prev(mEndChunk))->GetObjects().end();
				}
			}

			Iterator& operator++() {
				mCurrentObject++;

				if (mCurrentObject == (*mCurrentChunk)->GetObjects().end()) {
					mCurrentChunk++;

					if (mCurrentChunk != mEndChunk) {
						VI_ASSERT(*mCurrentChunk != nullptr && "Invalid memory chunk");
						mCurrentObject = (*mCurrentChunk)->GetObjects().begin();
					}
				}

				return *this;
			}

			VI_FORCE_INLINE T* operator*() const { return *mCurrentObject; }
			VI_FORCE_INLINE T* operator->() const { return *mCurrentObject; }

			bool operator==(const Iterator& other) const {
				return mCurrentChunk == other.mCurrentChunk && mCurrentObject == other.mCurrentObject;
			}
			
			bool operator!=(const Iterator& other) const {
				return !(*this == other);
			}
		private:
			typename MemoryChunkList::iterator mCurrentChunk;
			typename MemoryChunkList::iterator mEndChunk;
			typename ObjectList::const_iterator mCurrentObject;
		};

	public:
		MemoryChunkManager(const char* usage, const MemoryConfiguration& config = MemoryConfiguration()) : mUsage(usage), MemoryManager(config) {

		}

		virtual ~MemoryChunkManager() {
		}

		void* Allocate() {
			void* memory = nullptr;
			
			for (MemoryChunk* memoryChunk : mMemoryChunkList) {
				if (!memoryChunk->HasSlot()) {
					continue;
				}

				return memoryChunk->Allocate();
			}

			if (memory == nullptr) {
				PoolAllocator* allocator = new PoolAllocator(
					MEMORY_CHUNK_MAX_SIZE,
					AllocateOnStack(mUsage, MEMORY_CHUNK_MAX_SIZE, alignof(T)),
					sizeof(T), alignof(T)
				);

				MemoryChunk* memoryChunk = new MemoryChunk(allocator);
				memory = memoryChunk->Allocate();
				mMemoryChunkList.emplace_back(memoryChunk);
			}

			VI_ASSERT(memory && "Failed to allocate new memory");

			return memory;
		}

		template<typename... Args>
		T* NewObject(Args&&... args) {
			void* address = Allocate();
			return new (address)T(std::forward<Args>(args)...);
		}

		void FreeObject(void* memory) {
			for (MemoryChunk* memoryChunk : mMemoryChunkList) {
				if (memoryChunk->Contains(memory)) {
					memoryChunk->Free(memory);
					return;
				}
			}

			CORE_LOG_WARN("Failed to free memory {0}, possible memory corruption");
		}

		void Reset() {
			for (auto iter = mMemoryChunkList.rbegin(); iter != mMemoryChunkList.rend(); ++iter) {
				FreeOnStack((*iter)->GetStartAddress());
				(*iter)->Clear();
				VI_FREE_MEMORY(*iter);
			}
			mMemoryChunkList.clear();
		}
		
		VI_FORCE_INLINE Iterator begin() { return Iterator(mMemoryChunkList.begin(), mMemoryChunkList.end()); }
		VI_FORCE_INLINE Iterator end() { return Iterator(mMemoryChunkList.end(), mMemoryChunkList.end()); }
	private:
		MemoryChunkList mMemoryChunkList;
		const char* mUsage;
	};
}