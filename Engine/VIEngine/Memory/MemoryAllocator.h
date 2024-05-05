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
		virtual void Free(void* memory) {}
		virtual void Clear() {}
	protected:
		uint8_t GetAddressAdjustment(const void* address, uint8_t alignment);
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
}