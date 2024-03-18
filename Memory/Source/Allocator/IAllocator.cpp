#include"IAllocator.h"

namespace VIMemory {
	IAllocator::IAllocator(size_t memoryCapacity, const void* startAddress) : 
			mMemorySize(memoryCapacity), mStartAddress(startAddress), mUsedMemory(0), mAllocationCount(0) {

	}

	IAllocator::~IAllocator() {
		Clear();
	}

	const void* IAllocator::GetStartAddress() {
		return mStartAddress;
	}

	uint8_t IAllocator::CalculateAddressAlignment(const void* address, uint8_t alignment) {
		assert(IsPowerOfTwo(alignment) && "Address alignment must be power of two");
		// This is the "%"" operator but faster
		uintptr_t modulo = reinterpret_cast<uintptr_t>(address) & (alignment - 1);
		return alignment - modulo;
	}

	size_t IAllocator::AlignForward(size_t memorySize, uint8_t alignment) {
		assert(IsPowerOfTwo(alignment) && "Address alignment must be power of two");
		uint8_t modulo = memorySize & (alignment - 1);
		if (modulo != 0) {
			memorySize += alignment - modulo;
		}
		return memorySize;
	}
	
	uintptr_t IAllocator::AlignForward(uintptr_t memorySize, uintptr_t alignment) {
		assert(IsPowerOfTwo(alignment) && "Address alignment must be power of two");
		uint8_t modulo = memorySize & (alignment - 1);
		if (modulo != 0) {
			memorySize += alignment - modulo;
		}
		return memorySize;
	}

	uint8_t IAllocator::CalculateAddressAlignment(const void* address, uint8_t alignment, uint8_t extraMemory) {
		assert(IsPowerOfTwo(alignment) && "Address alignment must be power of two");

		uint8_t originalAdjustment = CalculateAddressAlignment(address, alignment);
		uint8_t extraAdjustment = 0;

		if (extraMemory > originalAdjustment) {
			extraMemory -= originalAdjustment;

			extraAdjustment = originalAdjustment + alignment * (extraMemory / alignment);

			if ((extraAdjustment & (alignment - 1)) != 0) {
				extraAdjustment += alignment;
			}
		}

		return extraAdjustment;
	}

	bool IAllocator::IsPowerOfTwo(uint8_t alignment) {
		return (alignment & (alignment - 1)) == 0;
	}
}