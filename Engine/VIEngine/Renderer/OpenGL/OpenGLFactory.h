#pragma once

#include"pch.h"
#include"Renderer/RendererAPI.h"

namespace VIEngine {
	class OpenGLFactory {
	public:
		static uint32_t ToOpenGLPrimitive(ERendererPrimitive primitive);
		static uint32_t ToOpenGLMode(ERendererMode mode);
	};
}