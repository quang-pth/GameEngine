#include"MemoryManager.h"

#include"Memory/Allocator/MemoryAllocator.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
    MemoryManager::MemoryManager(size_t memorySize)
        : mMemorySize(memorySize)
    {

    }

    void MemoryManager::Init(EMemoryAllocator allocator) {
        mAddress = malloc(mMemorySize);
        mAllocator.reset(MemoryAllocator::Create(allocator, mMemorySize, mAddress));

        VI_ASSERT(mAllocator != nullptr && "Failed to allocate memory");

        mPendingMemories.clear();
        mFreedMemories.clear();
    }

    void MemoryManager::Shutdown() {
        mAllocator->Release();

        free(mAddress);
        mAddress = nullptr;

        mPendingMemories.clear();
        mFreedMemories.clear();
    }

    void* MemoryManager::Allocate(size_t memorySize, uint8_t alignment, const char* usage) {
        void* memory = mAllocator->Allocate(memorySize, alignment);
        mPendingMemories.push_back({ usage, memory });
        return memory;
    }

    void MemoryManager::Free(void* memory) {
        if (!mPendingMemories.empty() && memory == mPendingMemories.back().second) {
            mAllocator->Free(memory);
            mPendingMemories.pop_back();

            bool remainedMemory = true;
            while (remainedMemory) {
                remainedMemory = false;

                for (auto iter : mFreedMemories) {
                    if (iter == mPendingMemories.back().second) {
                        mAllocator->Free(iter);
                        mPendingMemories.pop_back();
                        mFreedMemories.remove(iter);

                        remainedMemory = true;
                        break;
                    }
                }
            }
        }
        else {
            mFreedMemories.emplace_back(memory);
        }
    }

    void MemoryManager::Release() {
        mAllocator->Release();
        mPendingMemories.clear();
    }

    void MemoryManager::DetecMemoryLeaks() {
        VI_ASSERT(!(mFreedMemories.size() > 0 && mPendingMemories.size() == 0) && "Implementation failure!");

        if (mPendingMemories.size() > 0)
        {
            CORE_LOG_WARN("!!!  M E M O R Y   L E A K   D E T E C T E D  !!!");
            CORE_LOG_WARN("!!!  M E M O R Y   L E A K   D E T E C T E D  !!!");
            CORE_LOG_WARN("!!!  M E M O R Y   L E A K   D E T E C T E D  !!!");

            for (auto& pendingIter : mPendingMemories)
            {
                bool isFreed = false;

                for (auto freedIter : mFreedMemories)
                {
                    if (pendingIter.second == freedIter)
                    {
                        isFreed = true;
                        break;
                    }
                }

                if (isFreed == false)
                {
                    CORE_LOG_WARN("\'%s\' memory user didn't release allocated memory %p!", pendingIter.first, pendingIter.second);
                }
            }
        }
        else
        {
            CORE_LOG_INFO("No memory leaks detected.");
        }
    }
} // namespace Engine::ECS::Memory