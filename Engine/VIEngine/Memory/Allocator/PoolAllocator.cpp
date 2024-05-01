#include"MemoryAllocator.h"

namespace VIEngine {
    PoolAllocator::PoolAllocator(size_t memorySize, const void* address, const size_t chunkSize, const uint8_t chunkAlignment)
        : MemoryAllocator(memorySize, address), mChunkAlignment(chunkAlignment), mChunkSize(chunkSize), mFreelistHead()
    {
        union {
            void* asVoidPtr;
            uintptr_t asUintPtr;
        };

        asVoidPtr = const_cast<void*>(mStartAddress);
        // Reset memory address to follow the chunk alignment
        uintptr_t startAddressAfterAlgined = MemoryAllocator::AlignForward(asUintPtr, static_cast<uintptr_t>(mChunkAlignment));
        size_t memoryDifferent = static_cast<size_t>(startAddressAfterAlgined - asUintPtr);
        mMemorySize -= memoryDifferent;

        mChunkSize = MemoryAllocator::AlignForward(mChunkSize, mChunkAlignment);
        VI_ASSERT(mChunkSize >= sizeof(PoolFreeNode) && "Invalid memory chunk size");
        VI_ASSERT(mMemorySize > mChunkSize && "Invalid memory size");
        mFreelistHead = nullptr;

        this->Clear();
    }

    void* PoolAllocator::AllocateChunk() {
        PoolFreeNode* node = mFreelistHead;
        VI_ASSERT(node != nullptr && "Head free node is null");
        mFreelistHead = node->Next;

        mUsedMemory += mChunkSize;
        mAllocationCount++;

        return node;
    }

    void* PoolAllocator::Allocate(size_t memorySize, uint8_t alignment) {
        return nullptr;
    }

    void PoolAllocator::Free(void* memory) {
        union {
            void* asVoidPtr;
            char* asCharPtr;
        };
        asVoidPtr = const_cast<void*>(mStartAddress);

        void* endAddress = &asCharPtr[mMemorySize];
        if (memory >= endAddress || memory < asVoidPtr) {
            return;
        }

        if (memory == nullptr) {
            return;
        }

        PoolFreeNode* node = reinterpret_cast<PoolFreeNode*>(memory);
        node->Next = mFreelistHead;
        mFreelistHead = node;

        mUsedMemory -= mChunkSize;
        mAllocationCount--;
    }

    void PoolAllocator::Clear() {
        if (mAllocationCount || mUsedMemory) return;

        size_t numberOfChunks = mMemorySize / mChunkSize;

        union {
            void* asVoidPtr;
            char* asCharPtr;
        };

        asVoidPtr = const_cast<void*>(mStartAddress);

        for (size_t idx = 0; idx < numberOfChunks; idx++) {
            PoolFreeNode* chunk = (PoolFreeNode*)(&asCharPtr[idx * mChunkSize]);
            // Push chunk to the head of the free list
            chunk->Next = mFreelistHead;
            mFreelistHead = chunk;
        }

        mUsedMemory = 0;
        mAllocationCount = 0;
    }
}