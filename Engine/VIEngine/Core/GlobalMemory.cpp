#include"GlobalMemory.h"

namespace VIEngine {
	GlobalMemoryUsage* GlobalMemoryUsage::sInstance = nullptr;

	GlobalMemoryUsage& GlobalMemoryUsage::Get() {
		if (sInstance == nullptr) {
			sInstance = new GlobalMemoryUsage();
		}

		return *sInstance;
	}

	GlobalMemoryUsage::GlobalMemoryUsage() : mMemoryManager() {

	}

	GlobalMemoryUsage::~GlobalMemoryUsage() {

	}

	void GlobalMemoryUsage::FreeOnStack(void* memory) {
		mMemoryManager.FreeOnStack(memory);
	}
}