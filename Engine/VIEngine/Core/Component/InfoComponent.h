#pragma once

#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"

namespace VIEngine {
	class VI_API InfoComponent : public ECS::Component<InfoComponent, Actor> {
	public:
		DECLARE_RTTI
	public:
		InfoComponent() = default;
		InfoComponent(const std::string& name);
		~InfoComponent();
		const std::string& GetName() const { return mName; }
		void SetName(const std::string& name) { mName = name; }
	private:
		std::string mName;
	};
}