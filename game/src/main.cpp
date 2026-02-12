#include "game.hpp"

#include <iostream>

int main() {

	cppengine::Window::getInstance().initialise();
	cppengine::Window::getInstance().createWindow(800, 600, "test window");
	cppengine::Graphics::getInstance().initialise();

	cppengine::SceneManager::getInstance().initialise();

	while (!cppengine::Window::getInstance().windowShouldClose()) {

		switch (cppengine::SceneManager::getInstance().getState()) {
			case cppengine::SceneState::SETUP:
				break;
			case cppengine::SceneState::UPDATE:
				cppengine::Window::getInstance().beginFrame();

				cppengine::Graphics::getInstance().beginDraw();

				cppengine::Graphics::getInstance().draw();

				cppengine::Graphics::getInstance().endDraw();

				cppengine::Window::getInstance().endFrame();
				cppengine::Time::getInstance().advance();
				break;
			case cppengine::SceneState::TEARDOWN:
				break;
			case cppengine::SceneState::INITIALISE:

				break;
		}

	}

	cppengine::SceneManager::getInstance().shutdown();
	cppengine::Graphics::getInstance().shutdown();
	cppengine::Window::getInstance().closeWindow();
	cppengine::Window::getInstance().shutdown();
	
	return 0;
}