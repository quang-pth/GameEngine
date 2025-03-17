#pragma once

#include"pch.h"
#include"Core/Application.h"
#include"RenderCommandQueue.h"
#include"BatchRenderer.h"
#include"RenderBatch.h"
#include"Memory/MemoryManager.h"

namespace VIEngine {
	struct VI_API RendererData {
		ERendererState RendererState = ERendererState::None;
	};
	
	class VI_API Renderer {
	public:
		static void Submit(const RenderCallback&);
		static void ClearColor(float r, float g, float b, float w = 1.0f);
		static void DrawIndexed(uint32_t nums, ERendererPrimitive primitive = ERendererPrimitive::Triangles, uint32_t offset = 0);
		static void SetAlphaState(bool enable = true, ERendererBlendFunction source = ERendererBlendFunction::SourceAlpha, ERendererBlendFunction destination = ERendererBlendFunction::OneMinusSourceAlpha, ERendererBlendEquation blendEquation = ERendererBlendEquation::Add);
		static void ActivateTexture(uint8_t index);
		static void BindTexture2D(uint8_t textureID);
		static void OnInit(const ApplicationConfiguration&, class Camera* camera);
		static bool BeginScene();
		static void Render();
		static void EndScene();
		static void OnShutDown();
		static void StartSpriteBatch();
		static void SubmitSpriteBatch(const SpriteBatch& spriteBatch);
		static void EndSpriteBatch();
		static void DrawQuad(float minX, float minY, float maxX, float maxY, const glm::vec3& color);
		static void DrawPolygon(glm::vec3* vertices, uint32_t count, const glm::vec3& color);
	private:
		static RenderCommandQueue sRenderCommandQueue;
		static class std::vector<BatchRenderer*> sBatchRenderers;
		static MemoryManager sMemoryManager;
		static class VertexArray* sQuadVertexArray;
		static class Shader* sPolygonShader;
		static class Camera* sCamera;
	public:
		~Renderer() = default;
	protected:
		Renderer() = default;
	};
}