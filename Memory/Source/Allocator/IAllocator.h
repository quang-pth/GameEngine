#pragma once

#include"Base.h"

namespace VIMemory {
	class VI_MEM_API IAllocator {
		DISALLOW_COPY_AND_ASSIGN(IAllocator)
	public:
		static uint8_t CalculateAddressAlignment(const void* address, uint8_t alignment);
		static size_t AlignForward(size_t memorySize, uint8_t alignment);
		static uintptr_t AlignForward(uintptr_t memorySize, uintptr_t alignment);
		static uint8_t CalculateAddressAlignment(const void* address, uint8_t alignment, uint8_t extraMemory);
		static bool IsPowerOfTwo(uint8_t alignment);
	public:
		IAllocator(size_t memoryCapacity, const void* startAddress);
		virtual ~IAllocator();
		const void* GetStartAddress();
		virtual void* Allocate(size_t size) = 0;
		virtual void Free(void* memory) = 0;
		virtual void Clear() = 0;
	protected:
		size_t mMemorySize;
		const void* mStartAddress;
		size_t mUsedMemory;
		size_t mAllocationCount;
	};

	class VI_MEM_API PoolAllocator : public IAllocator {
		struct PoolFreeNode {
			PoolFreeNode* Next;
		};
	public:
		PoolAllocator(size_t memoryCapacity, const void* startAddress, size_t chunkSize, uint8_t chunkAligment);
		~PoolAllocator();
		void* AllocateChunk();
		virtual void* Allocate(size_t size) override;
		virtual void Free(void* memory) override;
		virtual void Clear() override;
	private:
		size_t mChunkSize;
		uint8_t mChunkAlignment;
		PoolFreeNode* mFreelistHead;
	};
}