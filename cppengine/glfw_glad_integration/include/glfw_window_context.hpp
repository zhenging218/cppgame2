#ifndef GLFW_WINDOW_CONTEXT_HPP
#define GLFW_WINDOW_CONTEXT_HPP
#include "platform/window_context.hpp"

namespace cppengine {
    class GLFWWindowContext : public WindowContext {
    private:
        GLFWwindow *window;
    public:
        GLFWWindowContext();

        GLFWWindowContext(GLFWWindowContext const &) = delete;
        GLFWWindowContext &operator=(GLFWWindowContext const &) = delete;

        void createWindow(int width, int height, const std::string &title) override;

        bool windowShouldClose() const override;

        void beginFrame() override;

        void endFrame() override;

        void closeWindow() override;

        int getWidth() const override;

        int getHeight() const override;

        ~GLFWWindowContext() override;

        GLFWwindow *getWindow() const;
    };
}

#endif
