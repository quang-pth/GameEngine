#pragma once

#include"pch.h"
#include"Core/Type/Object.h"

namespace VIEngine {
	class VI_API Shader : public Object {
	public:
		DECLARE_RTTI
	public:
		virtual ~Shader() = default;
		virtual uint32_t GetID() const = 0;
	protected:
		Shader() = default;
	};
}