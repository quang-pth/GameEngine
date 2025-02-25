#pragma once

#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"
#include"Animation/Animation.h"
#include<glm/glm.hpp>

namespace VIEngine {
	class VI_API AnimatorComponent : public ECS::Component<AnimatorComponent, Actor> {
	public:
		DECLARE_RTTI
	public:
		AnimatorComponent();
		~AnimatorComponent();
		void AddAnimation(Animation* animation);
		void SetActiveAnimation(const std::string& name);
		void SetActiveAnimation(UUID hashNameID);
		Animation* GetAnimation(const std::string& name) const;
		Animation* GetAnimation(UUID hashNameID) const;
		VI_FORCE_INLINE Animation* GetActiveAnimation() const { return mAnimationMap.at(mActiveAnimationID); }
		VI_FORCE_INLINE void SetFPS(float fps) { mFPS = fps; }
		VI_FORCE_INLINE float GetFPS() const { return mFPS; }
		VI_FORCE_INLINE void SetFrameTime(float frameTime) { mFrameTime = frameTime; }
		VI_FORCE_INLINE float GetFrameTime() const { return mFrameTime; }
		VI_FORCE_INLINE uint8_t GetCurrentFrameIdx() const { return mCurrentFrameIdx; }
		VI_FORCE_INLINE uint8_t SetFrameIdx(uint8_t frameIdx) { mCurrentFrameIdx = frameIdx; }
		void NextFrame();
		class Sprite* CurrentFrame();
		void SetColor(const glm::vec4& color);
		bool GetFlipVertical() const { return mFlipVertical; }
		void SetFlipVertical(bool value) { mFlipVertical = value; }
		bool GetFlipHorizontal() const { return mFlipHorizontal; }
		void SetFlipHorizontal(bool value) { mFlipHorizontal = value; }
		bool IsActiveAnimationFinished();
	private:
		std::unordered_map<UUID, Animation*> mAnimationMap;
		UUID mActiveAnimationID;
		float mFPS;
		float mFrameTime;
		bool mFlipVertical = false;
		bool mFlipHorizontal = false;
		uint8_t mCurrentFrameIdx = 0;
	};
}