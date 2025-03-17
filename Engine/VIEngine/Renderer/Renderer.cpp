#include"Renderer.h"
#include"Core/Logger/Logger.h"
#include"Core/Application.h"
#include"RenderCommand.h"
#include"Resource/Shader.h"
#include"Resource/VertexArray.h"
#include"Resource/VertexBuffer.h"
#include"Resource/IndexBuffer.h"
#include"Renderer/Camera/Camera.h"
#include<glm/gtc/matrix_transform.hpp>
#include<glad/gl.h>

namespace VIEngine {
	RenderCommandQueue Renderer::sRenderCommandQueue;
	std::vector<BatchRenderer*> Renderer::sBatchRenderers;
	MemoryManager Renderer::sMemoryManager;
	VertexArray* Renderer::sQuadVertexArray = nullptr;
	Shader* Renderer::sPolygonShader = nullptr;
	Camera* Renderer::sCamera = nullptr;

	void Renderer::Submit(const RenderCallback& renderCallback) {
		// if (Application::Get().GetPerFrameData().IsCatchUpPhase) return;

		sRenderCommandQueue.Enqueue(renderCallback);
	}

	void Renderer::ClearColor(float r, float g, float b, float w) {
		Submit([r, g, b, w]() {
			RenderCommand::ClearColor(r, g, b, w);
		});
	}

	void Renderer::DrawIndexed(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) {
		Submit([nums, primitive, offset]() {
			RenderCommand::DrawIndexed(nums, primitive, offset);
		});
	}

	void Renderer::SetAlphaState(bool enable, ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) {
		Submit([enable, source, destination, blendEquation]() {
			RenderCommand::SetAlphaState(enable, source, destination, blendEquation);
		});
	}

	void Renderer::ActivateTexture(uint8_t index) {
		Submit([index]() {
			RenderCommand::ActivateTexture(index);
		});
	}

	void Renderer::BindTexture2D(uint8_t textureID) {
		Submit([textureID]() {
			RenderCommand::BindTexture2D(textureID);
		});
	}

	void Renderer::OnInit(const ApplicationConfiguration& appConfig, Camera* camera) {
		sCamera = camera;
		sBatchRenderers.push_back(sMemoryManager.NewPerFrame<BatchRenderer>());
		sBatchRenderers.back()->SetCamera(sCamera);

		sPolygonShader = Shader::Create("Assets/Shader/quad.glsl");
		Submit([rendererSpec = appConfig.RendererSpec]() {
			RenderCommand::OnInit(rendererSpec);
			CORE_LOG_INFO("Renderer init success");
		});
	}

	bool Renderer::BeginScene() {
		return true;
	}

	void Renderer::Render() {
		sRenderCommandQueue.ProcessAndRender();
	}

	void Renderer::EndScene() {
	}

	void Renderer::OnShutDown() {
		Submit([]() {
			RenderCommand::OnShutdown();
			for (auto iter = sBatchRenderers.begin(); iter != sBatchRenderers.end(); ++iter) {
				sBatchRenderers.erase(iter);
			}
			sBatchRenderers.clear();
			CORE_LOG_INFO("Renderer is shutdown");
		});
	}

	void Renderer::StartSpriteBatch() {
		// TODO: Fix memory leaks here later
		// sBatchRenderers.push_back(sMemoryManager.NewPerFrame<BatchRenderer>());
		sBatchRenderers.back()->Begin();
	}

	void Renderer::SubmitSpriteBatch(const SpriteBatch& spriteBatch) {
		if (Application::Get().GetPerFrameData().IsCatchUpPhase) return;
		sBatchRenderers.back()->InsertBatch(spriteBatch);
	}

	void Renderer::EndSpriteBatch() {
		sBatchRenderers.back()->End();
		// sBatchRenderers.clear();
	}

	void Renderer::DrawQuad(float minX, float minY, float maxX, float maxY, const glm::vec3& color) {
		VI_ASSERT(sCamera != nullptr && "Camera is not set");

		sPolygonShader->Bind();
		sPolygonShader->SetMatrix4("viewMatrix", sCamera->GetViewMatrix());
		sPolygonShader->SetMatrix4("projectionMatrix", sCamera->GetProjectionMatrix());
		sPolygonShader->SetVector3("quadColor", color);

		float vertices[] = {
			minX, minY, 0.0f, // Bottom Left
			minX, maxY, 0.0f, // Top Left
			maxX, maxY, 0.0f, // Top Right
			maxX, minY, 0.0f, // Bottom Right
		};
		uint32_t indices[] = {
			0, 1, // Left Vertical Line
			1, 2, // Top Horizontal Line
			2, 3, // Right Vertical Line
			3, 0 // Bottom Horizontal Line
		};

		VertexFormat format;
		format.AddAttribute(EVertexAttributeType::Float3, "aPosition");
		VertexArray* vertexArray = VertexArray::Create(format);
		vertexArray->Bind();
		vertexArray->SetVertexBuffer(vertices, sizeof(vertices), ERendererMode::Dynamic);
		vertexArray->SetIndexBuffer(indices, sizeof(indices), sizeof(indices) / sizeof(uint32_t), ERendererMode::Dynamic);

		Submit([vertexArray = vertexArray]() {
			RenderCommand::DrawIndexed(vertexArray->GetIndexBuffer()->GetNums(), ERendererPrimitive::Lines);
		});
		vertexArray->Release();
	}

	void Renderer::DrawPolygon(glm::vec3* vertices, uint32_t count, const glm::vec3& color) {
		VI_ASSERT(sCamera != nullptr && "Camera is not set");

		sPolygonShader->Bind();
		sPolygonShader->SetMatrix4("viewMatrix", sCamera->GetViewMatrix());
		sPolygonShader->SetMatrix4("projectionMatrix", sCamera->GetProjectionMatrix());
		sPolygonShader->SetVector3("quadColor", color);

		VertexFormat format;
		format.AddAttribute(EVertexAttributeType::Float3, "aPosition");
		VertexArray* vertexArray = VertexArray::Create(format);
		vertexArray->Bind();
		vertexArray->SetVertexBuffer(vertices, sizeof(glm::vec3) * count, ERendererMode::Dynamic);

		Submit([vertexArray = vertexArray, count = count]() {
			RenderCommand::DrawArrays(count, ERendererPrimitive::LinesLoop);
		});
		vertexArray->Release();
	}
}