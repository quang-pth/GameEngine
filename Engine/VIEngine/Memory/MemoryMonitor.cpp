#include"MemoryMonitor.h"

namespace VIEngine {
	MemoryMonitor* MemoryMonitor::sInstance = nullptr;

	MemoryMonitor& MemoryMonitor::Get() {
		if (sInstance == nullptr) {
			sInstance = new MemoryMonitor();
		}

		return *sInstance;
	}

	MemoryMonitor::MemoryMonitor() {

	}

	MemoryMonitor::~MemoryMonitor() {

	}


	void MemoryMonitor::Add(MemoryManager* memoryUsage) {
		if (memoryUsage != nullptr) {
			mUsages.push_back(memoryUsage);
		}
	}
	
	void MemoryMonitor::Remove(MemoryManager* memoryUsage) {
		auto iter = std::find(mUsages.begin(), mUsages.end(), memoryUsage);

		if (iter != mUsages.end()) {
			(*iter)->Clear();
			(*iter)->DetecMemoryLeaks();
			mUsages.erase(iter);
		}
	}

	void MemoryMonitor::Update() {
		for (auto usage : mUsages) {
			if (usage != nullptr) {
				usage->Update();
			}
		}
	}

	void MemoryMonitor::Clear() {
		for (auto usage : mUsages) {
			if (usage != nullptr) {
				usage->Clear();
			}
		}
	}
	
	void MemoryMonitor::DectecMemoryLeaks() {
		for (auto usage : mUsages) {
			if (usage != nullptr) {
				usage->DetecMemoryLeaks();
			}
		}
	}
}