#pragma once

#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"
#include"Core/Type/Collision.h"

namespace VIEngine {
	class VI_API InfoComponent : public ECS::Component<InfoComponent, Actor> {
	public:
		DECLARE_RTTI
	public:
		InfoComponent() = default;
		InfoComponent(const std::string& name);
		~InfoComponent();
		VI_FORCE_INLINE const std::string& GetName() const { return mName; }
		VI_FORCE_INLINE void SetName(const std::string& name) { mName = name; }
		VI_FORCE_INLINE uint64_t GetCategoryBits() const { return mCategoryBits; }
		VI_FORCE_INLINE void SetCategoryBits(uint64_t category) { mCategoryBits = category; }
		VI_FORCE_INLINE uint64_t GetMaskBits() const { return mMaskBits; }
		VI_FORCE_INLINE void SetMaskBits(uint64_t mask) { mMaskBits = mask; }
		VI_FORCE_INLINE int32_t GetGroupIndex() const { return mGroupIndex; }
		VI_FORCE_INLINE void SetGroupIndex(int32_t index) { mGroupIndex = index; }
		private:
		std::string mName;
		uint64_t mCategoryBits = ECategory::NONE;
		uint64_t mMaskBits = ECategory::STATIC | ECategory::DYNAMIC;
		int32_t mGroupIndex = 0;
	};
}