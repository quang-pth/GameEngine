#include"MemoryAllocator.h"

namespace VIEngine {
	MemoryAllocator::MemoryAllocator(size_t memorySize, void* address) : 
			mMemorySize(memorySize), mStartAddress(address), mUsedMemory(0), mAllocationCount(0) 
	{

	}

	uint8_t MemoryAllocator::GetAddressAdjustment(const void* address, uint8_t alignment) {
		VI_ASSERT(IsPowerOfTwo(alignment) && "Alignment is invalid");

		/*
			0101 = 5 (address = 0x0101)
			&
			0011 = 3 (alignment = 4)
			0001 -> 1

			-> offset = alignment - 1 = 4 - 1 = 3 -> adjusted address = 0x1000
		*/

		uintptr_t remainder = reinterpret_cast<uintptr_t>(address) & (alignment - 1);
		if (remainder == 0) {
			return 0;
		}

		return alignment - remainder;
	}
	
	uint8_t MemoryAllocator::GetAddressAdjustment(const void* address, uint8_t alignment, uint8_t extraMemory) {
		VI_ASSERT(IsPowerOfTwo(alignment) && "Alignment is invalid");

		uint8_t padding = GetAddressAdjustment(address, alignment);
		if (padding < extraMemory) {
			uint8_t remainPadding = extraMemory - padding;

			if ((remainPadding & (alignment - 1)) != 0) {
				padding += alignment * (1 + (remainPadding / alignment));
			}
			else {
				padding += alignment * (remainPadding / alignment);
			}
		}

		return padding;
	}

	size_t MemoryAllocator::AlignForward(size_t memorySize, uint8_t alignment) {
		VI_ASSERT(IsPowerOfTwo(alignment) && "Alignment is invalid");

		uintptr_t remainder = memorySize & (alignment - 1);
		if (remainder != 0) {
			memorySize += alignment - remainder;
		}

		return memorySize;
	}

	bool MemoryAllocator::IsPowerOfTwo(uint8_t alignment) {
		/*
			0100 = 4
			&
			0011 = 3
			0000 -> true
			
			0101 = 5
			&
			0100 = 4
			0100 -> false
		*/
		return (alignment & (alignment - 1)) == 0;
	}
}