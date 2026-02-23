#ifndef GLFW_WINDOW_CONTEXT_HPP
#define GLFW_WINDOW_CONTEXT_HPP
#include "platform/window_context.hpp"

namespace cppengine {
    class GLFWWindowContext : public WindowContext {
    private:

    public:
        void createWindow(int width, int height, const std::string &title) override;

        bool windowShouldClose() const override;

        void beginFrame() override;

        void endFrame() override;

        void closeWindow() override;

        int getWidth() const override;

        int getHeight() const override;

        ~GLFWWindowContext() override;
    };
}

#endif
