#include<VIEngine/Core/Entry.h>
#include<VIEngine/Window/Window.h>
#include<Core/Logger/Logger.h>

#include"GameplayLayer.h"

class Game : public VIEngine::Application {
public:
	Game(const VIEngine::ApplicationConfiguration& config) : VIEngine::Application(config) {
	}

	virtual void OnInitClient() override {
		LOG_INFO("Game is init");
		
		mLayer = new GameplayLayer();
		mUI = new UILayer();
		PushOverlayLayer(mUI);
		PushLayer(mLayer);
	}

	virtual void OnShutdownClient() override {
		LOG_INFO("Game is shutdown");
		PopLayer(mLayer);
		PopOverlayLayer(mUI);
	}
private:
	VIEngine::Layer* mLayer, *mUI;
};

VIEngine::Application* VIEngine::CreateApplication() {
	VIEngine::ApplicationConfiguration appConfig;
	appConfig.Width = 800;
	appConfig.Height = 600;
	appConfig.Title = "VIEngine Alpha ver";
	appConfig.WindowSpec = VIEngine::EWindowPlatformSpec::GLFW;

	return new Game(appConfig);
}