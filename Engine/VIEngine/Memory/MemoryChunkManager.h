#pragma once

#include"pch.h"
#include"Memory/Allocator/MemoryAllocator.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
    template<typename T, size_t MaxObjectsPerChunk>
    class MemoryChunkManager : public GlobalMemory {
        static const size_t MEMORY_CHUNK_MAX_SIZE = (sizeof(T) + alignof(T)) * MaxObjectsPerChunk;

        using ObjectList = std::list<T*>;

        class MemoryChunk {
        public:
            MemoryChunk(PoolAllocator* allocator) : mFreedAddresses() {
                mAllocator.reset(allocator);
                mStartAddress = reinterpret_cast<uintptr_t>(mAllocator->GetStartAddress());
                mEndAddress = mStartAddress + MEMORY_CHUNK_MAX_SIZE;
                mObjects.clear();
            }

            void Shutdown() {
                mObjects.clear();
                mAllocator->Release();
            }

            void* AllocateChunk() {
                if (!mFreedAddresses.empty()) {
                    void* memory = mFreedAddresses.front();
                    new (memory)T();
                    mFreedAddresses.pop();
                    return memory;
                }

                void* memory = mAllocator->AllocateChunk();
                mObjects.emplace_back(new (memory)T());
                return memory;
            }

            void Free(void* memory) {
                mAllocator->Free(memory);
                mFreedAddresses.push(memory);
            }

            bool HasSlot() {
                if (mFreedAddresses.size()) {
                    return true;
                }

                return mObjects.size() < MaxObjectsPerChunk;
            }

            const ObjectList& GetObjects() {
                return mObjects;
            }

            bool Contains(void* memory) {
                uintptr_t asUinptr = reinterpret_cast<uintptr_t>(memory);
                return asUinptr >= mStartAddress && asUinptr < mEndAddress;
            }

            void* GetStartAddress() { return const_cast<void*>(mAllocator->GetStartAddress()); }

        private:
            Unique<PoolAllocator> mAllocator;
            ObjectList mObjects;
            uintptr_t mStartAddress;
            uintptr_t mEndAddress;
            std::queue<void*> mFreedAddresses;
        };

        using MemoryChunkList = std::list<MemoryChunk*>;

        //==============================================ITERATOR========================================================
        class iterator
        {
        public:
            iterator(typename MemoryChunkList::iterator begin, typename MemoryChunkList::iterator end) :
                mCurrentChunk(begin),
                mEnd(end)
            {
                if (begin != end)
                {
                    VI_ASSERT((*mCurrentChunk) != nullptr);
                    mCurrentObject = (*mCurrentChunk)->GetObjects().begin();
                }
                else
                {
                    mCurrentObject = (*std::prev(mEnd))->GetObjects().end();
                }
            }


            VI_FORCE_INLINE iterator& operator++()
            {
                mCurrentObject++;

                if (mCurrentObject == (*mCurrentChunk)->GetObjects().end())
                {
                    mCurrentChunk++;

                    if (mCurrentChunk != mEnd)
                    {
                        VI_ASSERT((*mCurrentChunk) != nullptr);
                        mCurrentObject = (*mCurrentChunk)->GetObjects().begin();
                    }
                }

                return *this;
            }

            VI_FORCE_INLINE T* operator*() const { return *mCurrentObject; }
            VI_FORCE_INLINE T* operator->() const { return *mCurrentObject; }

            VI_FORCE_INLINE bool operator==(const iterator& other) const {
                bool chunkIsEqual = this->mCurrentChunk == other.mCurrentChunk;
                if (!chunkIsEqual) return false;
                return this->mCurrentObject == other.mCurrentObject;
            }

            VI_FORCE_INLINE bool operator!=(const iterator& other) const {
                return !(*this == other);
            }
        private:
            typename MemoryChunkList::iterator	mCurrentChunk;
            typename MemoryChunkList::iterator	mEnd;
            typename ObjectList::const_iterator mCurrentObject;
        };
        // ====================================================END ITERATOR==================================================

    public:
        MemoryChunkManager(const char* allocatorTag) : mAllocatorTag(allocatorTag), mMemoryChunks() {
            Init();
        }

        virtual ~MemoryChunkManager() {
            Shutdown();
        }

        virtual void Init(enum class EMemoryAllocator allocatorType = EMemoryAllocator::Stack) override {
            GlobalMemory::Init(allocatorType);
            PoolAllocator* allocator = new PoolAllocator(MEMORY_CHUNK_MAX_SIZE, 
                GlobalMemory::Allocate(MEMORY_CHUNK_MAX_SIZE, alignof(T), mAllocatorTag), 
                sizeof(T), alignof(T)
            );
            VI_ASSERT(allocator != nullptr && "Cannot initialize memory chunk manager");
            mMemoryChunks.emplace_back(new MemoryChunk(allocator));
        }

        virtual void Shutdown() override {
            for (auto iter = mMemoryChunks.rbegin(); iter != mMemoryChunks.rend(); iter++) {
                (*iter)->Shutdown();
                GlobalMemory::Free((*iter)->GetStartAddress());
            }
            mMemoryChunks.clear();
            GlobalMemory::Shutdown();
        }

        void* Allocate() {
            void* memory = nullptr;

            for (MemoryChunk* memoryChunk : mMemoryChunks) {
                if (!memoryChunk->HasSlot()) {
                    continue;
                }

                memory = memoryChunk->AllocateChunk();
                return memory;
            }

            // All memory chunks was full then allocate a new memory chunk
            if (memory == nullptr) {
                PoolAllocator* allocator = new PoolAllocator(
                    MEMORY_CHUNK_MAX_SIZE,
                    GlobalMemory::Allocate(MEMORY_CHUNK_MAX_SIZE, alignof(T), mAllocatorTag),
                    sizeof(T), alignof(T)
                );

                MemoryChunk* memoryChunk = new MemoryChunk(allocator);
                memory = memoryChunk->AllocateChunk();
                mMemoryChunks.emplace_back(memoryChunk);
            }

            VI_ASSERT(memory != nullptr && "Failed to allocate new memory");

            return memory;
        }

        void Free(void* memory) {
            for (MemoryChunk* memoryChunk : mMemoryChunks) {
                if (memoryChunk->Contains(memory)) {
                    memoryChunk->Free(memory);
                    return;
                }
            }

            CORE_LOG_WARN("Failed to free memory, warning possible memory corruption");
        }

        VI_FORCE_INLINE iterator begin() {
            return iterator(mMemoryChunks.begin(), mMemoryChunks.end());
        }

        VI_FORCE_INLINE iterator end() {
            return iterator(mMemoryChunks.end(), mMemoryChunks.end());
        }

    private:
        MemoryChunkList mMemoryChunks;
        const char* mAllocatorTag;
    };
}