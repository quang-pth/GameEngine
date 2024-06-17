#pragma once

#include"RTTI.h"
#include"pch.h"

namespace VIEngine {
	class VI_API Object {
	public:
		DECLARE_RTTI
	public:
		VI_FORCE_INLINE bool IsTypeOf(const RTTI& other) const { return GetRunTimeTypeInfo().IsTypeOf(other); }
		VI_FORCE_INLINE bool IsDerivedFrom(const RTTI& other) const { return GetRunTimeTypeInfo().IsDerivedFrom(other); }

		VI_FORCE_INLINE bool IsExactlyTypeOf(const Object* obj) const { return obj && GetRunTimeTypeInfo().IsTypeOf(obj->GetRunTimeTypeInfo()); }
		VI_FORCE_INLINE bool IsExactlyDerivedFrom(const Object* obj) const { return obj && GetRunTimeTypeInfo().IsDerivedFrom(obj->GetRunTimeTypeInfo()); }
	};
}
