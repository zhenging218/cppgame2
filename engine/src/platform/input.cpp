#include "engine.hpp"

namespace cppengine {
    Input &Input::getInstance() {
        static Input instance;
        return instance;
    }

    void Input::initialise() {
        context = createContext();
    }

    void Input::shutdown() {

    }

    void Input::getInputs() {

    }

    bool Input::isKeyUp(KeyCode keyCode) {
        return getInstance().context->isKeyUp(keyCode);
    }

    bool Input::isKeyDown(KeyCode keyCode) {
        return getInstance().context->isKeyDown(keyCode);
    }

    bool Input::isKeyPressed(KeyCode keyCode) {
        return getInstance().context->isKeyPressed(keyCode);
    }

    bool Input::isKeyReleased(KeyCode keyCode) {
        return getInstance().context->isKeyReleased(keyCode);
    }
}
