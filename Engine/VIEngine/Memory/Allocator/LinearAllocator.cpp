#include"MemoryAllocator.h"

namespace VIEngine
{
    LinearAllocator::LinearAllocator(size_t memorySize, const void* address)
        : MemoryAllocator(memorySize, address)
    {

    }

    void* LinearAllocator::Allocate(size_t memorySize, uint8_t alignment) {
        VI_ASSERT(memorySize > INVALID_MEMORY_SIZE && "Allocate called with size less than zero");
        VI_ASSERT(alignment < MAX_ALIGNMENT_ALLOWED && "Alignment must be less than 128 bytes");

        union {
            void* asVoidPtrAddress;
            uintptr_t asUintPtrAddress;
        };

        asVoidPtrAddress = const_cast<void*>(mStartAddress);
        asUintPtrAddress += mUsedMemory;

        uintptr_t adjustment = MemoryAllocator::CalculateAddressAlignment(asVoidPtrAddress, alignment);

        if (mUsedMemory + memorySize + adjustment > mMemorySize) {
            return nullptr;
        }

        asUintPtrAddress += adjustment;
        mUsedMemory += memorySize + adjustment;
        mAllocationCount += 1;

        memset(asVoidPtrAddress, 0, memorySize);
        return asVoidPtrAddress;
    }

    void LinearAllocator::Free(void* memory) {
        VI_ASSERT(false && "Arena Allocator does not support Free(), use Clear() instead");
    }

    void LinearAllocator::Clear() {
        if (mUsedMemory || mAllocationCount);

        mUsedMemory = 0;
        mAllocationCount = 0;
    }
} // namespace Engine::ECS::Memory