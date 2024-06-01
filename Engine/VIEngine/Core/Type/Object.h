#pragma once

#include"RTTI.h"

namespace VIEngine {
	class VI_API Object {	
	public:
		VI_FORCE_INLINE bool IsTypeOf(const	RTTI& rtti) const { return GetRTTI().IsTypeOf(rtti); }
		VI_FORCE_INLINE bool IsDerivedFrom(const RTTI& rtti) const { return GetRTTI().IsDerivedFrom(rtti); }
		VI_FORCE_INLINE bool IsExactlyTypeOf(const Object* obj) const { return obj && GetRTTI().IsTypeOf(obj->GetRTTI()); }
		VI_FORCE_INLINE bool IsExactlyDerivedFrom(const Object* obj) const { return obj && GetRTTI().IsDerivedFrom(obj->GetRTTI()); }
	public:
		DECLARE_RTTI
	};

	DEFINE_RTTI_NO_PARENT(VIEngine::Object);

	class VI_API Actor : public Object {
	public:
		DECLARE_RTTI
	};

	DEFINE_RTTI(VIEngine::Actor, &Object::RunTimeType);

	class VI_API GameObject : public Actor {
	public:
		DECLARE_RTTI
	};

	DEFINE_RTTI(VIEngine::GameObject, &Actor::RunTimeType);
}