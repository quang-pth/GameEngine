#include"AnimatorComponent.h"
#include"Resource/VertexBuffer.h"
#include"Resource/VertexArray.h"
#include"Resource/Shader.h"
#include"Resource/Sprite.h"
#include<glm/glm.hpp>

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(AnimatorComponent)

	AnimatorComponent::AnimatorComponent() : 
		mActiveAnimationID(), mFPS(24), mFrameTime(0.0f) 
	{
		
	}

	AnimatorComponent::~AnimatorComponent() {

	}

	void AnimatorComponent::AddAnimation(Animation* animation) {
		UUID nameHashID = GetHashID(animation->GetName());
		if (mAnimationMap.count(nameHashID)) {
			CORE_LOG_WARN("Adding duplicated animation name, replace the already existed!");
		}

		mAnimationMap[nameHashID] = animation;
		SetActiveAnimation(animation->GetName());
	}

	void AnimatorComponent::SetActiveAnimation(const std::string& name)
	{
		UUID nameHashID = GetHashID(name);
		if (mAnimationMap.count(nameHashID)) {
			mActiveAnimationID = nameHashID;
		}
		else {
			CORE_LOG_WARN("Invalid animation name has been set {0}", name.c_str());
		}
	}

	void AnimatorComponent::SetActiveAnimation(UUID hashNameID)
	{
		if (mAnimationMap.count(hashNameID)) {
			mActiveAnimationID = hashNameID;
		}
		else {
			CORE_LOG_WARN("Invalid animation hash name id has been set");
		}
	}

	Animation* AnimatorComponent::GetAnimation(const std::string& name) const
	{
		UUID nameHashID = GetHashID(name);
		VI_ASSERT(mAnimationMap.count(nameHashID) > 0 && "Invalid animation name");
		return mAnimationMap.at(nameHashID);
	}

	Animation* AnimatorComponent::GetAnimation(UUID hashNameID) const
	{
		VI_ASSERT(mAnimationMap.count(hashNameID) > 0 && "Invalid animation hash name");
		return mAnimationMap.at(hashNameID);
	}

	void AnimatorComponent::SetColor(const glm::vec4& color) {
		for (auto& [_, animation] : mAnimationMap) {
			for (Sprite* sprite : animation->GetSprites()) {
				sprite->SetColor(color);
			}
		}
	}
}