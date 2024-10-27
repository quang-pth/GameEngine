#pragma once

#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"

namespace VIEngine {
	class VI_API TransformComponent : public ECS::Component<TransformComponent, Actor> {
	public:
		DECLARE_RTTI
	public:
		TransformComponent() = default;
		TransformComponent(float x, float y) : mX(x), mY(y) {}
		~TransformComponent() {}

		float GetX() const { return mX; }
		void SetX(float value) { mX = value; }
		float GetY() const { return mY; }
		void SetY(float value) { mY = value; }
	private:
		float mX, mY;
	};
}