#ifndef GLFW_INPUT_CONTEXT_HPP
#define GLFW_INPUT_CONTEXT_HPP
#include "platform/input_context.hpp"

namespace cppengine {
    class GLFWInputContext : public InputContext {
    private:

    public:
        GLFWInputContext();
        ~GLFWInputContext() override;

        void clearInputs();

        bool isKeyUp(KeyCode keyCode) const override;

        bool isKeyDown(KeyCode keyCode) const override;

        bool isKeyPressed(KeyCode keyCode) const override;

        bool isKeyReleased(KeyCode keyCode) const override;
    };
}

#endif