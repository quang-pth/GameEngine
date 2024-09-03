#pragma once

#include"RenderCommandCallback.h"
#include"Memory/MemoryManager.h"

namespace VIEngine {
	class RenderCommandQueue {
	public:
		static void Enqueue(const RenderCallback& commandCallback);
		static void ProcessAndRender();
	protected:
		RenderCommandQueue() = default;
	private:
		static std::vector<RenderCommandCallback*> sCallbackQueue;
		static MemoryManager sMemoryManager;
	};
}