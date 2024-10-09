#pragma once

namespace VIEngine {
	enum class ERendererSpec {
		OpenGL,
		DirectX
	};

	enum class ERendererMode {
		Static,
		Dynamic,
		Stream
	};

	enum class ERendererResource {
		VertexShader,
		FragmentShader,
		Shader
	};

	enum class ERendererPrimitive {
		Triangles,
		Points,
		Lines
	};

	enum class ERendererState {
		Blending,
		DepthTesting,
		StencilTesting,
		FaceCulling,
		MultiSample,
		Enable,
		Disable,
		None
	};

	enum class ERendererBlendEquation {
		Add,
		Subtract,
		ReverseSubtract,
		Min,
		Max,
		None
	};

	enum class ERendererBlendFunction {
		Zero,
		One,
		SourceAlpha,
		OneMinusSourceAlpha,
		DestinationAlpha,
		OneMinusDestionaAlpha,
		None
	};

	enum class ETextureFormat {
		RED,
		RGB,
		RGBA
	};

	enum class ETextureWrapMode {
		Repeat,
		Clamp,
		Mirror,
		Border
	};

	enum class ETextureFilter {
		Linear,
		Nearest,
		NearestMipMapNearest,
		NearestMipMapLinear,
		LinearMipMapLinear,
		LinearMipMapNearest
	};
}