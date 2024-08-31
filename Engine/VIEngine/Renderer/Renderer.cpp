#include"Renderer.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(Renderer)

	Renderer::Renderer() {

	}

	Renderer::~Renderer() {

	}

	void Renderer::OnInit() {
		CORE_LOG_TRACE("Renderer init success");
	}

	bool Renderer::BeginScene() {
		return true;
	}

	void Renderer::Render() {

	}

	void Renderer::EndScene() {

	}

	void Renderer::ShutDown() {
		CORE_LOG_TRACE("Renderer is shutdown");
	}
}