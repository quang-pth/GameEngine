#pragma once

#include"pch.h"

namespace VIEngine {
	using RenderCallback = std::function<void()>;

	class RenderCommandCallback {
	public:
		RenderCommandCallback();
		RenderCommandCallback(const RenderCallback& renderCallback);
		~RenderCommandCallback();

		void Execute();
		VI_FORCE_INLINE uint32_t GetFrameIndex() const { return mFrameIndex; }
		VI_FORCE_INLINE void SetFrameIndex(uint32_t frameIndex) { mFrameIndex = frameIndex; }
	private:
		RenderCallback mCallback;
		uint32_t mFrameIndex;
	};
}