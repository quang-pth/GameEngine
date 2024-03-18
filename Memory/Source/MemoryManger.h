#pragma once

#include"Base.h"

namespace VIMemory {
	class VI_MEM_API MemoryManager {
	public:
		static void* Allocate(uint32_t size);
	};
}