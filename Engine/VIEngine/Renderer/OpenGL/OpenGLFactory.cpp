#include"OpenGLFactory.h"

#include<glad/gl.h>

namespace VIEngine {
	uint32_t OpenGLFactory::ToOpenGLMode(ERendererMode mode) {
		if (mode == ERendererMode::Dynamic) return GL_DYNAMIC_DRAW;
		if (mode == ERendererMode::Stream) return GL_STREAM_DRAW;

		return GL_STATIC_DRAW;
	}

	uint32_t OpenGLFactory::ToOpenGLPrimitive(ERendererPrimitive primitive) {
		if (primitive == ERendererPrimitive::Points) return GL_POINTS;
		if (primitive == ERendererPrimitive::Lines) return GL_LINES;

		return GL_TRIANGLES;
	}
}