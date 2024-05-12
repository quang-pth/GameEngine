#include"MemoryAllocator.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
	StackAllocator::StackAllocator(size_t memorySize, void* address) : MemoryAllocator(memorySize, address) {

	}

	StackAllocator::~StackAllocator() {

	}

	void* StackAllocator::Allocate(size_t memorySize, uint8_t alignment) {
		VI_ASSERT(memorySize > INVALID_MEMORY_SIZE && "Allocate invalid memory size");
		VI_ASSERT(alignment < MAX_ALLOWED_ALIGNMENT && "Invalid alignment");

		union {
			void* asVoidPtrAddress;
			uintptr_t asUintPtrAddress;
			Header* asHeader;
		};

		asVoidPtrAddress = mStartAddress;
		asUintPtrAddress += mUsedMemory;

		uintptr_t padding = GetAddressAdjustment(asVoidPtrAddress, alignment, sizeof(Header));

		if (mUsedMemory + padding + memorySize > mMemorySize) {
			CORE_LOG_WARN("StackAllocator is full, can not allocate for new data with size {0}", memorySize);
			return nullptr;
		}

		mUsedMemory += memorySize + padding;

		asUintPtrAddress += padding;
		asUintPtrAddress -= sizeof(Header);
		asHeader->Padding = padding;
		asUintPtrAddress += sizeof(Header);

		mAllocationCount++;

		return asVoidPtrAddress;
	}

	void StackAllocator::Free(void* memory) {
		union {
			void* asVoidPtrAddress;
			uintptr_t asUintPtrAddress;
			Header* asHeader;
		};

		asVoidPtrAddress = memory;
		uintptr_t startMemory = reinterpret_cast<uintptr_t>(mStartAddress);
		bool isInBounds = asUintPtrAddress >= startMemory && asUintPtrAddress < startMemory + mMemorySize;
		VI_ASSERT(isInBounds && "Free out-of-bounds memory address");

		asUintPtrAddress -= sizeof(Header);
		mUsedMemory = reinterpret_cast<uintptr_t>(memory) - startMemory - asHeader->Padding;
		mAllocationCount--;
	}

	void StackAllocator::Clear() {
		mUsedMemory = 0;
		mAllocationCount = 0;
	}
}