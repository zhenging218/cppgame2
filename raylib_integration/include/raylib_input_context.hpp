#ifndef RAYLIB_INPUT_CONTEXT_HPP
#define RAYLIB_INPUT_CONTEXT_HPP
#include "platform/input_context.hpp"

namespace cppengine {
    class RaylibInputContext : public InputContext {

    public:
        bool isKeyUp(KeyCode keyCode) const override;
        bool isKeyDown(KeyCode keyCode) const override;
        bool isKeyPressed(KeyCode keyCode) const override;
        bool isKeyReleased(KeyCode keyCode) const override;

        ~RaylibInputContext() override = default;
    };
}

#endif
