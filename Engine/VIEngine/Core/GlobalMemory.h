#pragma once

#include"pch.h"
#include"Memory/MemoryManager.h"

namespace VIEngine {
	class VI_API GlobalMemoryUsage {
	public:
		static GlobalMemoryUsage& Get();
	private:
		static GlobalMemoryUsage* sInstance;

	public:
		~GlobalMemoryUsage();

		void FreeOnStack(void* memory);

		// Allocate temporary memory that will be automatically freed at the end of a frame
		template<typename T, typename... Args>
		T* NewPerFrame(Args&&... args) {
			return mMemoryManager.NewPerFrame<T>(std::forward<Args>(args)...);
		}

		template<typename T, typename... Args>
		T* NewOnStack(const char* usage, Args&&... args) {
			return mMemoryManager.NewOnStack<T>(usage, std::forward<Args>(args)...);
		}

	protected:
		GlobalMemoryUsage();

	private:
		MemoryManager mMemoryManager;
	};
}