#include"MemoryAllocator.h"

namespace VIEngine {
    StackAllocator::StackAllocator(size_t memorySize, const void* address)
        : MemoryAllocator(memorySize, address)
    {

    }

    void* StackAllocator::Allocate(size_t memorySize, uint8_t alignment) {
        VI_ASSERT(memorySize > INVALID_MEMORY_SIZE && "Allocate called with size less than zero");
        VI_ASSERT(alignment < MAX_ALIGNMENT_ALLOWED && "Alignment must be less than 128 bytes");

        union {
            void* asVoidPtrAddress;
            uintptr_t asUintPtrAddress;
            MemoryHeader* asMemoryHeader;
        };

        asVoidPtrAddress = const_cast<void*>(mStartAddress);
        asUintPtrAddress += mUsedMemory;

        uintptr_t adjustment = CalculateAddressAlignment(asVoidPtrAddress, alignment, sizeof(MemoryHeader));

        if (mUsedMemory + adjustment + memorySize > mMemorySize) {
            return nullptr;
        }

        // Update stack memory
        mUsedMemory += memorySize + adjustment;
        mAllocationCount++;
        // Update Header
        asMemoryHeader->Adjustment = adjustment;

        // Return aligned addressed after take the header into account
        asUintPtrAddress += adjustment;

        return asVoidPtrAddress;
    }

    void StackAllocator::Free(void* memory) {
        union {
            void* asVoidPtrAddress;
            uintptr_t asUintPtrAddress;
            MemoryHeader* asMemoryHeader;
        };

        asVoidPtrAddress = memory;
        asUintPtrAddress -= sizeof(MemoryHeader);

        mUsedMemory = reinterpret_cast<uintptr_t>(memory) - reinterpret_cast<uintptr_t>(mStartAddress) - asMemoryHeader->Adjustment;
        mAllocationCount--;
    }

    void StackAllocator::Clear() {
        if (mUsedMemory || mAllocationCount) return;

        mUsedMemory = 0;
        mAllocationCount = 0;
    }
}