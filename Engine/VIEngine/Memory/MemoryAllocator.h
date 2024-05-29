#pragma once

#include"pch.h"

namespace VIEngine {
	const uint8_t INVALID_MEMORY_SIZE = 0;
	const uint8_t MAX_ALLOWED_ALIGNMENT = 128;

	class VI_API MemoryAllocator {
	public:
		MemoryAllocator(size_t memorySize, void* address);
		virtual ~MemoryAllocator() = default;
		virtual void* Allocate(size_t memorySize, uint8_t alignment) { return nullptr; }
		virtual void* Allocate() { return nullptr; }
		virtual void Free(void* memory) {}
		virtual void Clear() {}
		void* GetStartAddress() const { return mStartAddress; }
	protected:
		uint8_t GetAddressAdjustment(const void* address, uint8_t alignment);
		uint8_t GetAddressAdjustment(const void* address, uint8_t alignment, uint8_t extraMemory);
		size_t AlignForward(size_t memorySize, uint8_t alignment);
		bool IsPowerOfTwo(uint8_t alignment);
	protected:
		void* mStartAddress;
		size_t mMemorySize;
		size_t mUsedMemory;
		size_t mAllocationCount;
	};

	class VI_API LinearAllocator : public MemoryAllocator {
	public:
		LinearAllocator(size_t memorySize, void* address);
		~LinearAllocator();
		virtual void* Allocate(size_t memorySize, uint8_t alignment) override;
		virtual void Free(void* memory) override;
		virtual void Clear() override;
	};

	class VI_API StackAllocator : public MemoryAllocator {
		struct Header {
			uint8_t Padding;
		};
	public:
		StackAllocator(size_t memorySize, void* address);
		~StackAllocator();
		virtual void* Allocate(size_t memorySize, uint8_t alignment) override;
		virtual void Free(void* memory) override;
		virtual void Clear() override;
	};

	class VI_API PoolAllocator : public MemoryAllocator {
		struct FreeNode {
			FreeNode* Next;
		};
	public:
		PoolAllocator(size_t memorySize, void* address, size_t chunkSize, uint8_t chunkAlignment);
		~PoolAllocator();
		virtual void* Allocate() override;
		virtual void Free(void* memory) override;
		virtual void Clear() override;
		bool Contains(void* memory);
	private:
		size_t mChunkSize;
		uint8_t mChunkAlignment;
		FreeNode* mFreeListHead;
		uint8_t mAddressOffset;
	};
}