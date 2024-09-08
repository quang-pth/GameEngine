#include"RenderCommandQueue.h"
#include"Core/Application.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
	RenderCommandQueue::RenderCommandQueue() : mRenderCommandCallbackQueue(), mMemoryManager() {

	}

	RenderCommandQueue::~RenderCommandQueue() {

	}

	void RenderCommandQueue::Enqueue(const RenderCallback& renderCallback) {
		RenderCommandCallback* renderCommandCallback = mMemoryManager.NewPerFrame<RenderCommandCallback>(renderCallback);
		VI_ASSERT(renderCommandCallback != nullptr && "Failed to allocate memory for render command");
		renderCommandCallback->SetFrameIndex(Application::Get().GetPerFrameData().FrameIndex);
		mRenderCommandCallbackQueue.push_back(renderCommandCallback);
		//CORE_LOG_TRACE("RenderCommand at frame {0} is allocated at address {1}", renderCommandCallback->GetFrameIndex(), (void*)renderCommandCallback);
	}

	void RenderCommandQueue::ProcessAndRender() {
		for (auto renderCommandCallback : mRenderCommandCallbackQueue) {
			renderCommandCallback->Execute();
		}
		mRenderCommandCallbackQueue.clear();
	}
}