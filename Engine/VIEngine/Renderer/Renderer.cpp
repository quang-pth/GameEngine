#include"Renderer.h"

#include"Core/Logger/Logger.h"

namespace VIEngine {
	Renderer::Renderer() {

	}

	Renderer::~Renderer() {
	}

	void Renderer::OnInit(ERendererAPI api) {
		mRendererAPI.reset(RendererAPIFactory::CreateRendererAPI(api));
	}

	void Renderer::OnShutdown() {
		MemoryManager::ClearOnStack();
		mRendererAPI.reset();
	}

	void Renderer::Submit(const RenderCommandCallback& commandCallback)
	{
		RenderCommand* command = MemoryManager::NewPerFrame<RenderCommand>(commandCallback);
		mCommandQueue.push(command);
	}

	void Renderer::BindVertexBufferImpl(const VertexBuffer* vertexBuffer)
	{
		mRendererAPI->BindVertexBufferImpl(vertexBuffer);
	}

	void Renderer::UnbindVertexBufferImpl(const VertexBuffer* vertexBuffer)
	{
		mRendererAPI->UnbindVertexBufferImpl(vertexBuffer);
	}

	void Renderer::BindIndexBufferImpl(const IndexBuffer* indexBuffer)
	{
		mRendererAPI->BindIndexBufferImpl(indexBuffer);
	}

	void Renderer::UnbindIndexBufferImpl(const IndexBuffer* indexBuffer)
	{
		mRendererAPI->UnbindIndexBufferImpl(indexBuffer);
	}

	void Renderer::BindShaderImpl(const Shader* shader)
	{
		mRendererAPI->BindShaderImpl(shader);
	}

	void Renderer::UnbindShaderImpl(const Shader* shader)
	{
		mRendererAPI->UnbindShaderImpl(shader);
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::Render()
	{
		while (!mCommandQueue.empty()) {
			mCommandQueue.front()->Execute();
			mCommandQueue.pop();
		}
	}

	void Renderer::EndScene()
	{
		MemoryManager::Clear();
	}
}