#pragma once

#include"RenderCommandCallback.h"
#include"Memory/MemoryManager.h"

namespace VIEngine {
	class RenderCommandQueue {
	public:
		RenderCommandQueue();
		~RenderCommandQueue();

		void Enqueue(const RenderCallback&);
		void ProcessAndRender();
	private:
		std::vector<RenderCommandCallback*> mRenderCommandCallbackQueue;
		MemoryManager mMemoryManager;
	};
}