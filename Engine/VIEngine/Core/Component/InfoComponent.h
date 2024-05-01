#pragma once

#include"pch.h"
#include"ECS/IComponent.h"

namespace VIEngine {
	class VI_API InfoComponent : public ECS::Component<InfoComponent> {
	public:
		InfoComponent() = default;
		InfoComponent(const std::string& name) : mName(name) {}
		VI_FORCE_INLINE const std::string& GetName() const { return mName; }
		VI_FORCE_INLINE void SetName(const std::string& name) { mName = name; }
	private:
		std::string mName;
	};
}