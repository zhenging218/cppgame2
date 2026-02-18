#ifndef INPUT_CONTEXT_HPP
#define INPUT_CONTEXT_HPP
#include "platform/enum_key_code.hpp"

namespace cppengine {
    class InputContext {
    private:

    public:
        virtual ~InputContext() = 0;
        virtual bool isKeyUp(KeyCode keyCode) const = 0;
        virtual bool isKeyDown(KeyCode keyCode) const = 0;
        virtual bool isKeyPressed(KeyCode keyCode) const = 0;
        virtual bool isKeyReleased(KeyCode keyCode) const = 0;
    };

    inline InputContext::~InputContext() = default;
}

#endif