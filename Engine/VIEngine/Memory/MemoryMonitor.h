#pragma once

#include"MemoryManager.h"

namespace VIEngine {
	class MemoryMonitor {
	public:
		static void Add(MemoryManager*);
		static void Remove(MemoryManager*);
		static void DetecsMemoryLeaks();
	private:
		static std::vector<MemoryManager*> sMemoryUsages;
	};
}