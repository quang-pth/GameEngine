#include"MemoryManger.h"

#include<malloc.h>

namespace VIMemory {
	void* MemoryManager::Allocate(uint32_t size) {
		return malloc(size);
	}
}