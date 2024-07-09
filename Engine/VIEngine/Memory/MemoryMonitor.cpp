#include"MemoryMonitor.h"

namespace VIEngine {
	std::vector<MemoryManager*> MemoryMonitor::sMemoryUsages;

	void MemoryMonitor::Add(MemoryManager* memoryUsage) {
		VI_ASSERT(memoryUsage != nullptr && "Monitor invalid memory usage");
		sMemoryUsages.push_back(memoryUsage);
	}

	void MemoryMonitor::Remove(MemoryManager* memoryUsage) {
		auto iter = std::find(sMemoryUsages.begin(), sMemoryUsages.end(), memoryUsage);
		if (iter != sMemoryUsages.end()) {
			sMemoryUsages.erase(iter);
		}
	}

	void MemoryMonitor::DetecsMemoryLeaks() {
		// TODO: fix memory leaks later for the component array
		for (MemoryManager* usage : sMemoryUsages) {
			usage->DetecMemoryLeaks();
		}
	}
}