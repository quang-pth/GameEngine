#include"MemoryAllocator.h"

namespace VIEngine
{
    MemoryAllocator* MemoryAllocator::Create(EMemoryAllocator allocator, size_t memorySize, const void* startAddress) {
        switch (allocator)
        {
            case EMemoryAllocator::Linear: return new LinearAllocator(memorySize, startAddress);
            case EMemoryAllocator::Stack: return new StackAllocator(memorySize, startAddress);
            case EMemoryAllocator::Pool: return new PoolAllocator(memorySize, startAddress);
        }

        return nullptr;
    }

    MemoryAllocator::MemoryAllocator(size_t memorySize, const void* address)
        : mMemorySize(memorySize), mStartAddress(address),
        mUsedMemory(0), mAllocationCount(0)
    {

    }

    void MemoryAllocator::Release() {
        this->Clear();
    }

    uintptr_t MemoryAllocator::CalculateAddressAlignment(const void* address, uint8_t alignment) {
        VI_ASSERT(IsPowerOfTwo(alignment) && "Address alignment must be power of two");
        // This is the "%"" operator but faster
        uintptr_t remainder = reinterpret_cast<uintptr_t>(address) & (alignment - 1);
        if (remainder == 0) {
            return 0;
        }

        return alignment - remainder;
    }

    size_t MemoryAllocator::AlignForward(size_t memorySize, uint8_t alignment) {
        VI_ASSERT(IsPowerOfTwo(alignment) && "Address alignment must be power of two");
        uint8_t remainder = memorySize & (alignment - 1);
        if (remainder != 0) {
            memorySize += alignment - remainder;
        }
        return memorySize;
    }

    uintptr_t MemoryAllocator::AlignForward(uintptr_t memorySize, uintptr_t alignment) {
        VI_ASSERT(IsPowerOfTwo(alignment) && "Address alignment must be power of two");
        uintptr_t remainder = memorySize & (alignment - 1);
        if (remainder != 0) {
            memorySize += alignment - remainder;
        }
        return memorySize;
    }

    uintptr_t MemoryAllocator::CalculateAddressAlignment(const void* address, uint8_t alignment, uintptr_t extraMemory) {
        VI_ASSERT(IsPowerOfTwo(alignment) && "Address alignment must be power of two");

        uintptr_t originalAdjustment = CalculateAddressAlignment(address, alignment);
        uintptr_t extraAdjustment = 0;

        if (extraMemory > originalAdjustment) {
            extraMemory -= originalAdjustment;

            extraAdjustment = originalAdjustment + alignment * (extraMemory / alignment);

            if ((extraAdjustment & (alignment - 1)) != 0) {
                extraAdjustment += alignment;
            }
        }

        return extraAdjustment;
    }

    bool MemoryAllocator::IsPowerOfTwo(uint8_t alignment) {
        return (alignment & (alignment - 1)) == 0;
    }
} // namespace Engine::ECS::Memory