#pragma once

#include"Core/Type/Actor.h"
#include"ECS/IComponent.h"
#include"Math/Math.h"

namespace VIEngine {
	class TransformComponent : public ECS::Component<TransformComponent, Actor> {
	public:
		DECLARE_RTTI
	public:
		TransformComponent() = default;
		TransformComponent(float x, float y) : mPosition(x, y) {}
		~TransformComponent() {}

		VI_FORCE_INLINE Math::Vector2& GetPosition() { return mPosition; }
		VI_FORCE_INLINE void SetPosition(const Math::Vector2& position) { mPosition = position; }

	private:
		Math::Vector2 mPosition;
	};

	DEFINE_RTTI_NO_PARENT(TransformComponent)
}