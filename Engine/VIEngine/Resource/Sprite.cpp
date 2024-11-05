#include"Sprite.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"Shader.h"
#include"Texture2D.h"
#include"ResourceManager.h"

namespace VIEngine {
	Sprite* Sprite::Create(const std::string& filepath) {
		return ResourceManager::Get().NewSprite(filepath);
	}

    Sprite::Sprite(const std::string& filepath) : mFilePath(filepath), mName(filepath), mVertexFormat() {
		mVertexFormat.AddAttribute(EVertexAttributeType::Float3, "aPosition");
		mVertexFormat.AddAttribute(EVertexAttributeType::Float2, "aTexCoords");
		mVertexFormat.AddAttribute(EVertexAttributeType::Float4, "aColor");

		Vertex vertices[4] = {
			{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f)}, // top-left
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f)}, // bottom-left
			{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f)}, // bottom-right
			{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f)} // top-right
		};

		uint32_t indicies[6] = {
			0, 1, 2, // left-bottom triangle
			2, 3, 0 // right-top triangle
		};

	    mVertexArray = VertexArray::Create(mVertexFormat);
		mVertexArray->SetVertexBuffer(vertices, sizeof(vertices));
		mVertexArray->SetIndexBuffer(indicies, sizeof(indicies), sizeof(indicies) / sizeof(uint32_t));
		mShader = Shader::Create("Assets/Shader/sprite.glsl");
        mTexture = Texture2D::Create(filepath);
    }

    Sprite::~Sprite() {
    }

	void Sprite::Release() {
        mTexture->Release();
        mVertexArray->Release();
        mShader->Release();
	}
}