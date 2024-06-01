#pragma once

#include"MemoryAllocator.h"

namespace VIEngine {
	struct MemoryConfiguration {
		// 10MB default buffer size for a single frame
		size_t PerFrameBufferSize = 10 * 1024 * 1024;
		// 10MB default buffer size for stack allocator
		size_t StackBufferSize = 10 * 1024 * 1024;
	};

	struct MemoryUsage {
		const char* ResouceName;
		void* ResouceAddress;
	};

	class MemoryManager {
	public:
		MemoryManager(const MemoryConfiguration& config = MemoryConfiguration());
		~MemoryManager();

		// Clear temporary memories on a single frame allocated by allocators
		void Update();
		
		// Clear all memories allocated by allocators
		void Clear();

		// Allocate temporary memory that will be automatically freed at the end of a frame
		void* AllocatePerFrame(size_t memorySize, uint8_t alignment);
		void* AllocateOnStack(const char* usage, size_t memorySize, uint8_t alignment);
		void FreeOnStack(void* memory);
		void ClearOnStack();
		void DetecMemoryLeaks();

		// Allocate temporary memory that will be automatically freed at the end of a frame
		template<typename T, typename... Args>
		T* NewPerFrame(Args&&... args) {
			void* address = mPerFrameAllocator.Allocate(sizeof(T), alignof(T));
			return new (address)T(std::forward<Args>(args)...);
		}

		template<typename T, typename... Args>
		T* NewOnStack(const char* usage, Args&&... args) {
			void* address = AllocateOnStack(usage, sizeof(T), alignof(T));
			return new (address)T(std::forward<Args>(args)...);
		}
	private:
		LinearAllocator mPerFrameAllocator;
		StackAllocator mStackAllocator;
		MemoryConfiguration mConfig;
		std::vector<MemoryUsage> mActiveMemories;
		std::vector<void*> mFreedMemories;
	};
}