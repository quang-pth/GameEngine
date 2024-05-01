#pragma once

#include"ECS/ISystem.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
	class VI_API InputSystem : public ECS::System<InputSystem> {
	public:
		InputSystem() = default;
		~InputSystem() = default;

		virtual void OnUpdate(Time time) override {
			CORE_LOG_TRACE("{0} is update at {1} interval", GetStaticTypeString(), GetUpdateInterval());
		}
	};

	class VI_API VRSystem : public ECS::System<VRSystem> {
	public:
		VRSystem() = default;
		~VRSystem() = default;

		virtual void OnUpdate(Time time) override {
			CORE_LOG_TRACE("{0} is update at {1} interval", GetStaticTypeString(), GetUpdateInterval());
		}
	};
}