#include "engine.hpp"

namespace cppengine {
    Window::Window() : context(nullptr) {

    }

    Window &Window::getInstance() {
        static Window window;
        return window;
    }

    void Window::initialise() {
        context = createContext();
    }

    void Window::createWindow(int width, int height, std::string const &title) {
        context->createWindow(width, height, title);
    }

    bool Window::windowShouldClose() const {
        return context->windowShouldClose();
    }

    void Window::beginFrame() {
        context->beginFrame();
    }

    void Window::endFrame() {
        context->endFrame();
    }

    void Window::closeWindow() {
        context->closeWindow();
    }

    void Window::shutdown() {
        context = nullptr;
    }

    int Window::getWidth() const {
        return context->getWidth();
    }

    int Window::getHeight() const {
        return context->getHeight();
    }
}
