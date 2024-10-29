#pragma once

#include"pch.h"
#include"Core/Input/InputState.h"
#include<glm/glm.hpp>

namespace VIEngine {
    const glm::vec3 AxisUnitX = glm::vec3(1.0f, 0.0f, 0.0f);
    const glm::vec3 AxisUnitY = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 AxisUnitZ = glm::vec3(0.0f, 0.0f, -1.0f);

    class Camera {
    public:
        Camera(const glm::mat4& projectionMatrix);
        ~Camera();
        void ProcessInput(const InputState&);
        void Update();
        void Focus();
        VI_FORCE_INLINE float GetDistance() const { return mDistance; }
        VI_FORCE_INLINE void SetDistance(float distance) { mDistance = distance; }
        VI_FORCE_INLINE const glm::mat4& GetViewMatrix() const { return mViewMatrix; }
        VI_FORCE_INLINE void SetViewMatrix(const glm::mat4& viewMatrix) { mViewMatrix = viewMatrix; }
        VI_FORCE_INLINE const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
        VI_FORCE_INLINE void SetProjectionMatrix(const glm::mat4& projectionMatrix) { mProjectionMatrix = projectionMatrix; }
        VI_FORCE_INLINE const glm::vec3& GetPosition() const { return mPosition; }
        glm::vec3 GetUpDirection();
        glm::vec3 GetRightDirection();
        glm::vec3 GetForwardDirection();
    private:
        void MousePan(const glm::vec2& delta);
        void MouseRotate(const glm::vec2& delta);
        void MouseZoom(float delta);
        glm::vec3 CalculatePosition();
        glm::quat GetOrientation();
    private:
        glm::mat4 mViewMatrix, mProjectionMatrix;
        glm::vec3 mPosition, mRotation, mFocalPoint;
        bool mIsPanning, mIsRotating;
        glm::vec2 mPreviousMousePosition;
        glm::vec3 mPreviousRotation, mPreviousFocalPoint;
        float mDistance;
        float mPanSpeed, mRotationSpeed, mZoomSpeed;
        float mPitch, mYaw;
    };
}