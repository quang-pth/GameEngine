#pragma once

#include"pch.h"

namespace VIEngine {
	class VI_API VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;
	protected:
		VertexBuffer() = default;
	};
}