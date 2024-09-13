#pragma once

namespace VIEngine {
	enum class ERendererSpec {
		OpenGL,
		DirectX
	};

	enum class ERendererResource {
		VertexBuffer,
		IndexBuffer,
		VertexShader,
		FragmentShader,
		ShaderProgram
	};

	enum class ERendererPrimitive {
		Triangles,
		TriangleStrip,
		Lines,
		Points
	};

	enum class ERendererMode {
		Static,
		Dynamic,
		Stream
	};
}