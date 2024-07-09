#pragma once

#include"pch.h"

namespace VIEngine {
	class VI_API Shader {
	public:
		virtual ~Shader() = default;
	protected:
		Shader() = default;
	};
}