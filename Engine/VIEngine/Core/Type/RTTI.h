#pragma once

namespace VIEngine {
	class RTTI {
	public:
		RTTI(const char* typeName, const RTTI* parent = nullptr);

		bool IsTypeOf(const RTTI& other) const;
		bool IsDerivedFrom(const RTTI& other) const;

		const char* GetTypeName() const;
		const RTTI* GetParentClass() const;
	private:
		const char* mTypeName;
		const RTTI* mParentClass;
	};
}

#define DECLARE_RTTI \
	static const VIEngine::RTTI RunTimeType; \
	virtual const VIEngine::RTTI& GetRunTimeTypeInfo() const;

#define DEFINE_RTTI(typeName, parent) \
	const VIEngine::RTTI typeName::RunTimeType(#typeName, &parent); \
	const VIEngine::RTTI& typeName::GetRunTimeTypeInfo() const { return RunTimeType; }

#define DEFINE_RTTI_NO_PARENT(typeName) \
	const VIEngine::RTTI typeName::RunTimeType(#typeName); \
	const VIEngine::RTTI& typeName::GetRunTimeTypeInfo() const { return RunTimeType; }