#include"MemoryManager.h"
#include"Core/Logger/Logger.h"
#include"MemoryMonitor.h"

namespace VIEngine {
	MemoryManager::MemoryManager(const MemoryConfiguration& config) : mConfig(config),
		mPerFrameAllocator(config.PerFrameBufferSize, malloc(config.PerFrameBufferSize)),
		mStackAllocator(config.StackBufferSize, malloc(config.StackBufferSize))
	{
		MemoryMonitor::Get().Add(this);
	}

	MemoryManager::~MemoryManager() {

	}

	void MemoryManager::Update() {
		mPerFrameAllocator.Clear();
	}

	void MemoryManager::Clear() {
		mPerFrameAllocator.Clear();
		mStackAllocator.Clear();
	}

	void* MemoryManager::AllocatePerFrame(size_t memorySize, uint8_t alignment) {
		return mPerFrameAllocator.Allocate(memorySize, alignment);
	}

	void* MemoryManager::AllocateOnStack(const char* usage, size_t memorySize, uint8_t alignment) {
		void* address = mStackAllocator.Allocate(memorySize, alignment);
		mActiveMemories.push_back({ usage, address });
		return address;
	}

	void MemoryManager::FreeOnStack(void* memory) {
		if (!mActiveMemories.empty() && memory == mActiveMemories.back().ResouceAddress) {
			mStackAllocator.Free(memory);
			mActiveMemories.pop_back();

			bool remainMemory = true;
			while (remainMemory) {
				remainMemory = false;

				for (auto iter = mFreedMemories.begin(); iter != mFreedMemories.end(); ++iter) {
					if (*iter == mActiveMemories.back().ResouceAddress) {
						mStackAllocator.Free(*iter);
						mActiveMemories.pop_back();
						mFreedMemories.erase(iter);
						remainMemory = true;
						break;
					}
				}
			}
		}
		else {
			CORE_LOG_WARN("User did not free memory {0} in order of stack", memory);
			mFreedMemories.emplace_back(memory);
		}
	}

	void MemoryManager::ClearOnStack() {
		mStackAllocator.Clear();
	}

	void MemoryManager::DetecMemoryLeaks() {
		VI_ASSERT(!(mFreedMemories.size() && mActiveMemories.size() == 0) && "Implementation failure!");

		if (mActiveMemories.size()) {
			CORE_LOG_WARN("!!!  M E M O R Y  L E A K  D E T E C T E D  !!!");

			for (auto& pendingMemory : mActiveMemories) {
				bool isFreed = false;

				for (auto freedMemory : mFreedMemories) {
					if (freedMemory == pendingMemory.ResouceAddress) {
						isFreed = true;
						break;
					}
				}

				if (isFreed == false) {
					CORE_LOG_WARN("{0} memory user did not release allocated memory {1}!", pendingMemory.ResouceName, pendingMemory.ResouceAddress);
				}
			}
		}
		else {
			CORE_LOG_INFO("No memory leaks detected");
		}
	}
}