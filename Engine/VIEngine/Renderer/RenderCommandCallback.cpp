#include"RenderCommandCallback.h"
#include"Core/Application.h"

namespace VIEngine {
	RenderCommandCallback::RenderCommandCallback() : mCallback(nullptr) {

	}
	
	RenderCommandCallback::RenderCommandCallback(const RenderCallback& renderCallback) : mCallback(renderCallback) {

	}

	RenderCommandCallback::~RenderCommandCallback() {

	}

	void RenderCommandCallback::Execute() {
		mCallback();
	}
}