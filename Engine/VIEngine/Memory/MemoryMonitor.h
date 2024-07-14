#pragma once

#include"MemoryManager.h"

namespace VIEngine {
	class MemoryMonitor {
	public:
		virtual ~MemoryMonitor() = default;
	public:
		static void Add(MemoryManager*);
		static void Remove(MemoryManager*);
		static void Update();
		static void Clear();
		static void DetecsMemoryLeaks();
	private:
		MemoryMonitor() = default;
	private:
		static std::vector<MemoryManager*> sMemoryUsages;
	};
}