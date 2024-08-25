#pragma once

#include"pch.h"
#include"MemoryManager.h"

namespace VIEngine {
	class VI_API MemoryMonitor {
	public:
		static MemoryMonitor& Get();
	private:
		static MemoryMonitor* sInstance;

	public:
		~MemoryMonitor();
	protected:
		MemoryMonitor();
	public:
		void Add(MemoryManager* memoryUsage);
		void Remove(MemoryManager* memoryUsage);
		void Update();
		void Clear();
		void DectecMemoryLeaks();
	private:
		std::vector<MemoryManager*> mUsages;
	};
}