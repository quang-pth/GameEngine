#pragma

#include"pch.h"

// Core
#include"Core/Logger/Logger.h"
#include"Core/Event/EventContext.h"
#include"Core/Type/Object.h"
#include"Memory/MemoryManager.h"

namespace VIEngine {
	template<typename T>
	VI_FORCE_INLINE T* StaticCast(Object* ptr) { return (T*)(ptr); }
	
	template<typename T>
	VI_FORCE_INLINE const T* StaticCast(const Object* ptr) { return (const T*)(ptr); }

	template<typename T>
	T* DownCast(Object* ptr) {
		if (ptr && ptr->IsDerivedFrom(T::RunTimeType)) {
			return (T*)(ptr);
		}

		return nullptr;
	}

	template<typename T>
	const T* DownCast(const Object* ptr) {
		if (ptr && ptr->IsDerivedFrom(T::RunTimeType)) {
			return (const T*)(ptr);
		}

		return nullptr;
	}
}