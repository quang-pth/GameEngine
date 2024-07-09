#pragma once

#include"pch.h"

namespace VIEngine {
	class VI_API IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;
	protected:
		IndexBuffer() = default;
	};
}