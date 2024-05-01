#include"EditorLayer.h"

#include<Core/Application.h>
#include<Core/Logger/Logger.h>
#include<Core/GameObject/GameObject.h>
#include<Core/Component/InfoComponent.h>

using namespace VIEngine;

EditorLayer::EditorLayer() {

}

EditorLayer::~EditorLayer() {

}

void EditorLayer::OnAttach() {
	Application& application = Application::GetInstance();

	for (int i = 0; i < 10000; i++) {
		GameObject obj = application.CreateGameObject();
		obj.AddComponent<InfoComponent>("Default");
		auto& infoComponent = obj.GetComponent<InfoComponent>();
		infoComponent.SetName("Obj" + std::to_string(i));
	}

	GameObject gameObject = application.CreateGameObject();
	gameObject.AddComponent<InfoComponent>("Default");
	auto& infoComponent = gameObject.GetComponent<InfoComponent>();
	infoComponent.SetName("Player");

	if (gameObject.HasComponent<InfoComponent>()) {
		gameObject.RemoveComponent<InfoComponent>();
	}

	gameObject.AddComponent<InfoComponent>("Player 2");
}

void EditorLayer::OnDetach() {

}