#include"RenderCommand.h"
#include"Core/GlobalMemory.h"

namespace VIEngine {
	RenderCommand* RenderCommand::sInstance = nullptr;

	void RenderCommand::OnInit(ERendererSpec rendererSpec) {
		switch (rendererSpec)
		{
		case VIEngine::ERendererSpec::OpenGL:
			sInstance = GlobalMemoryUsage::Get().NewOnStack<OpenGLRenderCommand>(OpenGLRenderCommand::RunTimeType.GetTypeName());
			break;
		case VIEngine::ERendererSpec::DirectX:
			VI_ASSERT(false && "Currently not supported for DirectX");
			break;
		default:
			VI_ASSERT(false && "Unknow Renderer API");
			break;
		}
	}

	void RenderCommand::OnShutdown() {

	}
}