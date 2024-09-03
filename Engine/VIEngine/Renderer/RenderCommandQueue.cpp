#include"RenderCommandQueue.h"
#include"Core/GlobalMemory.h"
#include"Core/Logger/Logger.h"
#include"Core/Application.h"

namespace VIEngine {
	std::vector<RenderCommandCallback*> RenderCommandQueue::sCallbackQueue;
	MemoryManager RenderCommandQueue::sMemoryManager;

	void RenderCommandQueue::Enqueue(const RenderCallback& commandCallback) {
		RenderCommandCallback* renderCommandCallback = sMemoryManager.NewPerFrame<RenderCommandCallback>(commandCallback);
		renderCommandCallback->SetFrameIndex(Application::Get().GetPerFrameData().FrameIndex);
		VI_ASSERT(renderCommandCallback != nullptr && "Failed to create render command");
		sCallbackQueue.push_back(renderCommandCallback);
		//CORE_LOG_TRACE("RenderCommand is allocated at {0} address for frame {1}", (void*)renderCommandCallback, renderCommandCallback->GetFrameIndex());
	}

	void RenderCommandQueue::ProcessAndRender() {
		//CORE_LOG_TRACE("Executing render command queue with size: {0}", mCallbackQueue.size());
		for (auto renderCallback : sCallbackQueue) {
			renderCallback->Execute();
		}
		sCallbackQueue.clear();
	}
}