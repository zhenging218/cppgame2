#include <cstring>

#include "game.hpp"

#include <iostream>

#include "raymath.h"

namespace {
	int run() {
		cppengine::Window::getInstance().initialise();
		cppengine::Window::getInstance().createWindow(800, 600, "test window");
		cppengine::Input::getInstance().initialise();
		cppengine::Renderer::getInstance().initialise();

		cppengine::SceneManager::getInstance().initialise();

		cppengine::SceneManager::getInstance().loadLevel<cppgame::TestLevel>();

		while (!cppengine::Window::getInstance().windowShouldClose()) {

			switch (cppengine::SceneManager::getInstance().getState()) {
				case cppengine::SceneState::LOAD:
					cppengine::SceneManager::getInstance().load();
					cppengine::Time::getInstance().reset();
					break;
				case cppengine::SceneState::INIT:
					cppengine::SceneManager::getInstance().init();
					break;
				case cppengine::SceneState::UPDATE:
					cppengine::Window::getInstance().beginFrame();
					cppengine::Input::getInstance().getInputs();
					cppengine::SceneManager::getInstance().update();
					cppengine::Renderer::getInstance().draw();
					cppengine::Window::getInstance().endFrame();
					cppengine::Time::getInstance().advance();
					break;
				case cppengine::SceneState::TEARDOWN:
					cppengine::SceneManager::getInstance().teardown();
					break;
				case cppengine::SceneState::UNLOAD:
					cppengine::SceneManager::getInstance().unload();
					break;

				case cppengine::SceneState::STARTUP:
					break;
			}

		}

		cppengine::SceneManager::getInstance().shutdown();
		cppengine::Renderer::getInstance().shutdown();
		cppengine::Input::getInstance().shutdown();
		cppengine::Window::getInstance().closeWindow();
		cppengine::Window::getInstance().shutdown();

		return 0;
	}
}

int main() {

	return run();
}