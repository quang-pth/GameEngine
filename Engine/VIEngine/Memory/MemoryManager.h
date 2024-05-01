#pragma once

#include"pch.h"
#include"Memory/Allocator/MemoryAllocator.h"

namespace VIEngine {
    class MemoryManager {
    public:
        MemoryManager() = default;
        MemoryManager(size_t memorySize);
        void Init(EMemoryAllocator allocator = EMemoryAllocator::Stack);
        void Shutdown();
        void* Allocate(size_t memorySize, uint8_t alignment, const char* usage = nullptr);
        void Free(void* memory);
        void Release();
        void DetecMemoryLeaks();
    private:
        MemoryManager(MemoryManager&) = delete;
        MemoryManager& operator=(MemoryManager&) = delete;
    private:
        void* mAddress;
        size_t mMemorySize;
        Unique<MemoryAllocator> mAllocator;
        std::vector<std::pair<const char*, void*>> mPendingMemories;
        std::list<void*> mFreedMemories;
    };
} // namespace Engine::ECS::Memory