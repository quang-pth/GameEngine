#pragma once

#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"
#include<glm/glm.hpp>

namespace VIEngine {
	struct VI_API Transform {
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
	};

	class VI_API TransformComponent : public ECS::Component<TransformComponent, Actor> {
	public:
		DECLARE_RTTI
	public:
		TransformComponent() = default;
		~TransformComponent() {}

		VI_FORCE_INLINE const Transform& GetTransform() const { return mTransform; }
		VI_FORCE_INLINE const glm::vec3& GetPosition() const { return mTransform.Position; }
		VI_FORCE_INLINE const glm::vec3& GetScale() const { return mTransform.Scale; }
		VI_FORCE_INLINE const glm::vec3& GetRotation() const { return mTransform.Rotation; }
		VI_FORCE_INLINE void SetPosition(float x, float y, float z) { mTransform.Position = { x, y, z }; }
		VI_FORCE_INLINE void SetPositionX(float x) { mTransform.Position.x = x; }
		VI_FORCE_INLINE void SetPositionY(float y) { mTransform.Position.y = y; }
		VI_FORCE_INLINE void SetPositionZ(float z) { mTransform.Position.z = z; }
		VI_FORCE_INLINE void SetScale(float x, float y, float z) { mTransform.Scale = { x, y, z }; }
		VI_FORCE_INLINE void SetScaleX(float x) { mTransform.Scale.x = x; }
		VI_FORCE_INLINE void SetScaleY(float y) { mTransform.Scale.y = y; }
		VI_FORCE_INLINE void SetScaleZ(float z) { mTransform.Scale.z = z; }
		VI_FORCE_INLINE void SetRotation(float x, float y, float z) { mTransform.Rotation = { x, y, z }; }
		VI_FORCE_INLINE void SetRotationX(float x) { mTransform.Rotation.x = x; }
		VI_FORCE_INLINE void SetRotationY(float y) { mTransform.Rotation.y = y; }
		VI_FORCE_INLINE void SetRotationZ(float z) { mTransform.Rotation.z = z; }
	private:
		Transform mTransform;
	};
}