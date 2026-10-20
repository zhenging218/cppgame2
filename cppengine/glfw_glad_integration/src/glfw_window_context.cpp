#include <mutex>
#include <shared_mutex>

#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    int width = 0;
    int height = 0;

    std::shared_mutex mutex;

    void safeSetWidthHeight(int width_, int height_) {
        std::unique_lock<std::shared_mutex> lock(mutex);
        width = width_;
        height = height_;
    }

    GLFWwindow *initGLFWAndSetWindowToNullptr() {
        if (!glfwInit()) {
            throw std::runtime_error("Could not initialise GLFW");
        }

        return nullptr;
    }

    void onGLFWWindowSizeEvent(GLFWwindow *window, int width_, int height_) {
        safeSetWidthHeight(width_, height_);
    }
}

namespace cppengine {
    GLFWWindowContext::GLFWWindowContext() : window(initGLFWAndSetWindowToNullptr()) {

    }

    void GLFWWindowContext::beginFrame() {
        GGContextManager::getInputContext()->clearInputs();
        glfwPollEvents();
    }

    void GLFWWindowContext::closeWindow() {
        glfwDestroyWindow(window);
    }

    void GLFWWindowContext::endFrame() {

    }

    int GLFWWindowContext::getHeight() const {
        std::shared_lock<std::shared_mutex> lock(mutex);
        return height;
    }

    int GLFWWindowContext::getWidth() const {
        std::shared_lock<std::shared_mutex> lock(mutex);
        return width;
    }

    bool GLFWWindowContext::windowShouldClose() const {
        return glfwWindowShouldClose(window);
    }

    GLFWWindowContext::~GLFWWindowContext() {
        glfwTerminate();
    }

    void GLFWWindowContext::createWindow(int width, int height, const std::string &title) {
        if (window == nullptr) {
            window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
            if (!window) {
                throw std::runtime_error(std::format(
                    "Could not create window ({} x {}) with title {}",
                    width, height, title));

            }

            safeSetWidthHeight(width, height);
            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);
            glfwSetWindowSizeCallback(window, &onGLFWWindowSizeEvent);
        }
    }

    GLFWwindow *GLFWWindowContext::getWindow() const {
        return window;
    }
}
