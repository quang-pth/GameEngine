#pragma once

#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"
#include"Animation/Animation.h"

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
		VI_FORCE_INLINE  Animation* GetActiveAnimation() const { return mActiveAnimation; }
		VI_FORCE_INLINE class VertexArray* GetVertexArray() const { return mVertexArray; }
		VI_FORCE_INLINE class Shader* GetShader() const { return mShader; }
		VI_FORCE_INLINE void SetFPS(float fps) { mFPS = fps; }
		VI_FORCE_INLINE float GetFPS() const { return mFPS; }
		VI_FORCE_INLINE void SetRuntime(float runtime) { mRuntime = runtime; }
		VI_FORCE_INLINE float GetRuntime() const { return mRuntime; }
		VI_FORCE_INLINE bool GetFlipHorizontal() const { return mFlipHorizontal; }
		VI_FORCE_INLINE void SetFlipHorizontal(bool flip) { mFlipHorizontal = flip; }
		VI_FORCE_INLINE bool GetFlipVertical() const { return mFlipVertical; }
		VI_FORCE_INLINE void SetFlipVertical(bool flip) { mFlipVertical = flip; }
	private:
		std::unordered_map<UUID, Animation*> mAnimationMap;
		Animation* mActiveAnimation;
		float mFPS;
		float mRuntime;
		class VertexArray* mVertexArray;
		class Shader* mShader;
		bool mFlipHorizontal, mFlipVertical;
	};
}