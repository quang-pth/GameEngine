#include"pch.h"

#include"Memory/MemoryManager.h"

namespace VIEngine {
	UUID GetUUID() {
		static std::random_device randomize;
		static std::mt19937_64 generator(randomize());
		static std::uniform_int_distribution<UUID> distribution;

		UUID uuid = INVALID_ID;
		do {
			uuid = distribution(generator);
		} while (uuid == INVALID_ID);

		return uuid;
	}

    GlobalMemory::GlobalMemory() : mMemoryManager() {
        mMemoryManager = new MemoryManager(MEMORY_GLOBAL_CAPACITY);
    }

    void GlobalMemory::Init(EMemoryAllocator allocator) {
        mMemoryManager->Init(allocator);
    }

    void GlobalMemory::Shutdown() {
        mMemoryManager->DetecMemoryLeaks();
        mMemoryManager->Shutdown();
        VI_FREE_MEMORY(mMemoryManager);
        mMemoryManager = nullptr;
    }

    void* GlobalMemory::Allocate(size_t memorySize, uint8_t alignment, const char* usage) {
        return mMemoryManager->Allocate(memorySize, alignment, usage);
    }

    void GlobalMemory::Free(void* memory) {
        mMemoryManager->Free(memory);
    }
}