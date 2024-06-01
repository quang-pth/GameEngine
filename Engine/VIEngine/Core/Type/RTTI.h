#pragma once

#include"pch.h"

namespace VIEngine {
	class VI_API RTTI {
	public:
		RTTI(const char* type, const RTTI* parent = nullptr);

		bool IsTypeOf(const RTTI& other) const;
		bool IsDerivedFrom(const RTTI& other) const;

		const char* GetTypeName() const;
		const RTTI* GetParentClass() const;
	private:
		const char* mType;
		const RTTI* mParentClass;
	};
}

#define DECLARE_RTTI \
	static const RTTI RunTimeType; \
	virtual const RTTI& GetRTTI() const;

#define DEFINE_RTTI(typeName, parent) \
	const RTTI typeName::RunTimeType(#typeName, parent); \
	const RTTI& typeName::GetRTTI() const { return RunTimeType; }

#define DEFINE_RTTI_NO_PARENT(typeName) \
	const RTTI typeName::RunTimeType(#typeName); \
	const RTTI& typeName::GetRTTI() const { return RunTimeType; }
