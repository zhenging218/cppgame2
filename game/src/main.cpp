#include "game.hpp"

#include <iostream>

int main() {

	cppengine::Window::getInstance().initialise();
	cppengine::Window::getInstance().createWindow(800, 600, "test window");
	cppengine::Graphics::getInstance().initialise();

	while (!cppengine::Window::getInstance().windowShouldClose()) {
		cppengine::Window::getInstance().beginFrame();
		cppengine::Graphics::getInstance().beginDraw();
		cppengine::Graphics::getInstance().draw();
		cppengine::Graphics::getInstance().endDraw();
		cppengine::Window::getInstance().endFrame();
	}

	cppengine::Graphics::getInstance().shutdown();
	cppengine::Window::getInstance().closeWindow();
	cppengine::Window::getInstance().shutdown();
	
	return 0;
}