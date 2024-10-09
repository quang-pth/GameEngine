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

	uint32_t OpenGLFactory::ToOpenGLState(ERendererState renderState) {
		if (renderState == ERendererState::DepthTesting) return GL_DEPTH_TEST;
		if (renderState == ERendererState::StencilTesting) return GL_STENCIL_TEST;
		if (renderState == ERendererState::FaceCulling) return GL_CULL_FACE;
		if (renderState == ERendererState::MultiSample) return GL_MULTISAMPLE;
		
		return GL_BLEND;
	}

	uint32_t OpenGLFactory::ToOpenGLBlendFunction(ERendererBlendFunction function)
	{
		if (function == ERendererBlendFunction::One) return GL_ONE;
		if (function == ERendererBlendFunction::SourceAlpha) return GL_SRC_ALPHA;
		if (function == ERendererBlendFunction::OneMinusSourceAlpha) return GL_ONE_MINUS_SRC_ALPHA;
		if (function == ERendererBlendFunction::DestinationAlpha) return GL_DST_ALPHA;
		if (function == ERendererBlendFunction::OneMinusDestionaAlpha) return GL_ONE_MINUS_DST_ALPHA;

		return GL_ZERO;
	}

	uint32_t OpenGLFactory::ToOpenGLBlendEquation(ERendererBlendEquation equation)
	{
		if (equation == ERendererBlendEquation::Subtract) return GL_FUNC_SUBTRACT;
		if (equation == ERendererBlendEquation::ReverseSubtract) return GL_FUNC_REVERSE_SUBTRACT;
		if (equation == ERendererBlendEquation::Min) return GL_MIN;
		if (equation == ERendererBlendEquation::Max) return GL_MAX;

		return GL_FUNC_ADD;
	}

	uint32_t OpenGLFactory::ToOpenGLFormat(ETextureFormat format)
	{
		if (format == ETextureFormat::RED) return GL_RED;
		if (format == ETextureFormat::RGB) return GL_RGB;

		return GL_RGBA;
	}

	uint32_t OpenGLFactory::ToOpenGLWrapMode(ETextureWrapMode mode)
	{
		if (mode == ETextureWrapMode::Clamp) return GL_CLAMP_TO_EDGE;
		if (mode == ETextureWrapMode::Mirror) return GL_MIRRORED_REPEAT;
		if (mode == ETextureWrapMode::Border) return GL_CLAMP_TO_BORDER;

		return GL_REPEAT;
	}

	uint32_t OpenGLFactory::ToOpenGLTextureFilter(ETextureFilter filter)
	{
		if (filter == ETextureFilter::Nearest) return GL_NEAREST;
		if (filter == ETextureFilter::NearestMipMapNearest) return GL_NEAREST_MIPMAP_NEAREST;
		if (filter == ETextureFilter::NearestMipMapLinear) return GL_NEAREST_MIPMAP_LINEAR;
		if (filter == ETextureFilter::LinearMipMapLinear) return GL_LINEAR_MIPMAP_LINEAR;
		if (filter == ETextureFilter::LinearMipMapNearest) return GL_LINEAR_MIPMAP_NEAREST;


		return GL_LINE;
	}
}