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
}