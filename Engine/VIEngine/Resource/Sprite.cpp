#include"Sprite.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"Shader.h"
#include"Texture2D.h"
#include"ResourceManager.h"
#include"VertexFormat.h"

namespace VIEngine {
	Sprite* Sprite::Create(const std::string& filepath) {
		return ResourceManager::Get().NewSprite(filepath);
	}

    Sprite::Sprite(const std::string& filepath) : mFilePath(filepath), mName(filepath) {
		VertexFormat vertexFormat;
		vertexFormat.AddAttribute(EVertexAttributeType::Float3, "aPosition");
		vertexFormat.AddAttribute(EVertexAttributeType::Float2, "aTexCoords");
		vertexFormat.AddAttribute(EVertexAttributeType::Int, "aTextureID");
		vertexFormat.AddAttribute(EVertexAttributeType::Int, "aFlipVertical");
		vertexFormat.AddAttribute(EVertexAttributeType::Int, "aFlipHorizontal");
		vertexFormat.AddAttribute(EVertexAttributeType::Float4, "aColor");

	    mVertexArray = VertexArray::Create();
		Vertex vertices[4] = {
			{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f), mColor}, // top-left
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), mColor}, // bottom-left
			{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), mColor}, // bottom-right
			{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f), mColor} // top-right
		};
		uint32_t indicies[6] = {
			0, 1, 2, // left-bottom triangle
			2, 3, 0 // right-top triangle
		};
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