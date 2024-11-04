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

	Vertex* Sprite::GetSharedVertexBuffer() {
		static Vertex vertices[4] = {
			{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f)}, // top-left
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f)}, // bottom-left
			{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f)}, // bottom-right
			{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f)} // top-right
		};

		return vertices;
	}

	uint32_t* Sprite::GetSharedIndexBuffer() {
		static uint32_t indicies[6] = {
			0, 1, 2, // left-bottom triangle
			2, 3, 0 // right-top triangle
		};

		return indicies;
	}

    Sprite::Sprite(const std::string& filepath) : mFilePath(filepath), mName(filepath), mVertexFormat() {
		mVertexFormat.AddAttribute(EVertexAttributeType::Float3, "aPosition");
		mVertexFormat.AddAttribute(EVertexAttributeType::Float2, "aTexCoords");
		mVertexFormat.AddAttribute(EVertexAttributeType::Float4, "aColor");

	    mVertexArray = VertexArray::Create(mVertexFormat);
		mVertexArray->SetVertexBuffer(GetSharedVertexBuffer(), mVertexFormat.GetStride());
		mVertexArray->SetIndexBuffer(GetSharedIndexBuffer(), sizeof(uint32_t) * 6, 6);
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