#include<VIEngine/Core/Entry.h>
#include<VIEngine/Window/Window.h>
#include<Core/Logger/Logger.h>

#include"Layer/EditorLayer.h"

class Game : public VIEngine::Application {
public:
	Game(const VIEngine::ApplicationConfiguration& config) : VIEngine::Application(config) {
	}

	virtual void OnInitClient() override {
		LOG_INFO("Game is init");

		mEditorLayer = new EditorLayer();
		PushLayer(mEditorLayer);
	}

	virtual void OnShutdownClient() override {
		PopLayer(mEditorLayer);

		LOG_INFO("Game is shutdown");
	}
private:
	VIEngine::Layer *mEditorLayer;
};

VIEngine::Application* VIEngine::CreateApplication() {
	VIEngine::ApplicationConfiguration appConfig;
	appConfig.Width = 800;
	appConfig.Height = 600;
	appConfig.Title = "VIEngine Alpha ver";
	appConfig.WindowSpec = VIEngine::EWindowPlatformSpec::GLFW;

	return new Game(appConfig);
}