#include"Application.h"

int main() {
	VIEngine::Application* application = VIEngine::CreateApplication();

	if (application->Init()) {
		application->Run();
	}

	application->Shutdown();
	delete application;

	return 0;
}