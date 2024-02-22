#include<VIEngine/Core/Entry.h>
#include<Core/Logger/Logger.h>

class Game : public VIEngine::Application {
public:
	Game(const VIEngine::ApplicationConfiguration& config) : VIEngine::Application(config) {
	}

	virtual bool Init() override {
		LOG_INFO("Game is init");
		return true;
	}

	virtual void Shutdown() override {
		LOG_INFO("Game is shutdown");
	}
};

VIEngine::Application* VIEngine::CreateApplication() {
	VIEngine::ApplicationConfiguration appConfig;
	appConfig.Width = 800;
	appConfig.Height = 600;
	appConfig.Title = "VIEngine Alpha ver";

	return new Game(appConfig);
}