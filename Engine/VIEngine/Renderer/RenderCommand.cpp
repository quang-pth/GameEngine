#include"RenderCommand.h"
#include"Core/GlobalMemory.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
	RenderCommand* RenderCommand::sInstance = nullptr;

	void RenderCommand::OnInit(ERendererSpec rendererSpec) {
		switch (rendererSpec)
		{
		case VIEngine::ERendererSpec::OpenGL: 
			sInstance = GlobalMemoryUsage::Get().NewOnStack<OpenGLRenderCommand>(OpenGLRenderCommand::RunTimeType.GetTypeName());
			CORE_LOG_INFO("Renderer is initialized with OpenGL");
			break;
		case VIEngine::ERendererSpec::DirectX:
			VI_ASSERT("Currently not support DirectX");
			break;
		default:
			VI_ASSERT("Unknown renderer api specified");
			break;
		}
	}

	void RenderCommand::OnShutdown() {

	}
}