#include"AnimatorComponent.h"
#include"Resource/VertexBuffer.h"
#include"Resource/VertexArray.h"
#include"Resource/Shader.h"
#include<glm/glm.hpp>

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(AnimatorComponent)

	AnimatorComponent::AnimatorComponent() : 
		mActiveAnimation(nullptr), mFPS(24), mRuntime(0.0f), mVertexArray(nullptr), mShader(),
		mFlipHorizontal(false), mFlipVertical(false)
	{
		mVertexArray = VertexArray::Create();
		Vertex vertices[4] = {
			{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // top-left
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // bottom-left
			{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // bottom-right
			{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)} // top-right
		};
		uint32_t indicies[6] = {
			0, 1, 2, // left-bottom triangle
			2, 3, 0 // right-top triangle
		};
		mVertexArray->SetVertexBuffer(vertices, sizeof(vertices));
		mVertexArray->SetIndexBuffer(indicies, sizeof(indicies), sizeof(indicies) / sizeof(uint32_t));
		mShader = Shader::Create("Assets/Shader/sprite.glsl");
	}

	AnimatorComponent::~AnimatorComponent() {

	}

	void AnimatorComponent::AddAnimation(Animation* animation) {
		VI_ASSERT(animation != nullptr && "Adding invalid animation");

		UUID nameHashID = GetHashID(animation->GetName());
		if (mAnimationMap.count(nameHashID)) {
			CORE_LOG_WARN("Adding duplicated animation name, replace the already existed!");
		}

		mAnimationMap[nameHashID] = animation;
	}

	void AnimatorComponent::SetActiveAnimation(const std::string& name)
	{
		UUID nameHashID = GetHashID(name);
		if (mAnimationMap.count(nameHashID)) {
			mActiveAnimation = mAnimationMap.at(nameHashID);
		}
		else {
			CORE_LOG_WARN("Invalid animation name has been set {0}", name.c_str());
		}
	}

	void AnimatorComponent::SetActiveAnimation(UUID hashNameID)
	{
		if (mAnimationMap.count(hashNameID)) {
			mActiveAnimation = mAnimationMap.at(hashNameID);
		}
		else {
			CORE_LOG_WARN("Invalid animation hash name id has been set");
		}
	}

	Animation* AnimatorComponent::GetAnimation(const std::string& name) const
	{
		UUID nameHashID = GetHashID(name);
		if (mAnimationMap.count(nameHashID)) {
			return mAnimationMap.at(nameHashID);
		}

		return nullptr;
	}

	Animation* AnimatorComponent::GetAnimation(UUID hashNameID) const
	{
		if (mAnimationMap.count(hashNameID)) {
			return mAnimationMap.at(hashNameID);
		}

		return nullptr;
	}
}