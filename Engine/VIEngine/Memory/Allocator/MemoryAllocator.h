#pragma once

#include"pch.h"

namespace VIEngine {
	const uint8_t INVALID_MEMORY_SIZE = 0;
	const uint8_t MAX_ALIGNMENT_ALLOWED = 128;

    enum class EMemoryAllocator {
        Linear,
        Stack,
        Pool
    };

	class VI_API MemoryAllocator {
    public:
        static MemoryAllocator* Create(EMemoryAllocator, size_t memorySize = 0, const void* startAddress = nullptr);
    public:
        MemoryAllocator(size_t memorySize, const void* address);
        virtual ~MemoryAllocator() = default;
    public:
        static uintptr_t CalculateAddressAlignment(const void* address, uint8_t alignment);
        static size_t AlignForward(size_t memorySize, uint8_t alignment);
        static uintptr_t AlignForward(uintptr_t memorySize, uintptr_t alignment);
        static uintptr_t CalculateAddressAlignment(const void* address, uint8_t alignment, uintptr_t extraMemory);
        static bool IsPowerOfTwo(uint8_t alignment);
    public:
        virtual void Release();
        const void* GetStartAddress() { return mStartAddress; }
        virtual void* Allocate(size_t memorySize, uint8_t alignment) { return nullptr; }
        virtual void Free(void* memory) {}
    protected:
        virtual void Clear() {}
    protected:
        const void* mStartAddress;
        size_t mMemorySize;
        size_t mUsedMemory;
        size_t mAllocationCount;
	};

    class VI_API LinearAllocator : public MemoryAllocator {
    public:
        LinearAllocator(size_t memorySize, const void* address);
        virtual void* Allocate(size_t memorySize, uint8_t alignment) override;
        virtual void Free(void* memory) override;
    protected:
        virtual void Clear() override;
    };

    class VI_API StackAllocator : public MemoryAllocator {
        struct MemoryHeader {
            size_t Adjustment;
        };

    public:
        StackAllocator(size_t memorySize, const void* address);
        virtual void* Allocate(size_t memorySize, uint8_t alignment) override;
        virtual void Free(void* memory) override;
    protected:
        virtual void Clear() override;
    };

    class VI_API PoolAllocator : public MemoryAllocator {
        struct PoolFreeNode {
            PoolFreeNode* Next;
        };
    public:
        PoolAllocator(size_t memorySize, const void* address, const size_t chunkSize = 128, const uint8_t chunkAlignment = 1);
        void* AllocateChunk();
        virtual void* Allocate(size_t memorySize, uint8_t alignment) override;
        virtual void Free(void* memory) override;
    protected:
        virtual void Clear() override;
    private:
        size_t mChunkSize;
        uint8_t mChunkAlignment;
        PoolFreeNode* mFreelistHead;
    };
}