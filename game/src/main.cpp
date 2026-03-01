#include <cstring>

#include "game.hpp"

#include <iostream>

namespace {
	using namespace cppengine;
	int run() {
		Window::getInstance().initialise();
		Window::getInstance().createWindow(800, 600, "test window");
		Input::getInstance().initialise();
		Renderer::getInstance().initialise();

		SceneManager::getInstance().initialise();

		SceneManager::getInstance().loadLevel<cppgame::TestLevel>();

		while (!Window::getInstance().windowShouldClose()) {

			switch (SceneManager::getInstance().getState()) {
				case SceneState::LOAD:
					SceneManager::getInstance().load();
					Time::getInstance().reset();
					break;
				case SceneState::INIT:
					SceneManager::getInstance().init();
					break;
				case SceneState::UPDATE:
					Window::getInstance().beginFrame();
					Input::getInstance().getInputs();
					SceneManager::getInstance().update();
					Renderer::getInstance().draw();
					Window::getInstance().endFrame();
					Time::getInstance().advance();
					break;
				case SceneState::TEARDOWN:
					SceneManager::getInstance().dispose();
					break;
				case SceneState::UNLOAD:
					SceneManager::getInstance().unload();
					break;

				case SceneState::STARTUP:
					break;
			}

		}

		SceneManager::getInstance().shutdown();
		Renderer::getInstance().shutdown();
		Input::getInstance().shutdown();
		Window::getInstance().closeWindow();
		Window::getInstance().shutdown();

		return 0;
	}
}

int main() {

	return run();
}