#include <cstring>

#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    bool keyIsDown[GLFW_KEY_LAST] = { false };
    bool keyIsPressed[GLFW_KEY_LAST] = { false };
    bool keyIsReleased[GLFW_KEY_LAST] = { false };

    bool mouseIsDown[GLFW_MOUSE_BUTTON_LAST] = { false };
    bool mouseIsPressed[GLFW_MOUSE_BUTTON_LAST] = { false };
    bool mouseIsReleased[GLFW_MOUSE_BUTTON_LAST] = { false };

    void onGlfwKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (!(key < 0) && key < GLFW_KEY_LAST) {
            switch (action) {
                case GLFW_PRESS:
                    keyIsDown[key] = true;
                    keyIsPressed[key] = true;
                    break;
                case GLFW_RELEASE:
                    keyIsDown[key] = false;
                    keyIsReleased[key] = true;
                    break;
                default:
                    break;
            }
        }
    }

    void onGLFWMouseEvent(GLFWwindow *window, int button, int action, int mods) {
        if (!(button < 0) && button < GLFW_MOUSE_BUTTON_LAST) {
            switch (action) {
                case GLFW_PRESS:
                    mouseIsDown[button] = true;
                    mouseIsPressed[button] = true;
                    break;
                case GLFW_RELEASE:
                    mouseIsDown[button] = false;
                    mouseIsReleased[button] = true;
                    break;
                default:
                    break;
            }
        }
    }

    int translateKeyCode(cppengine::KeyCode keyCode) {
        switch (keyCode) {
            case cppengine::KeyCode::A: return GLFW_KEY_A;
            case cppengine::KeyCode::B: return GLFW_KEY_B;
            case cppengine::KeyCode::C: return GLFW_KEY_C;
            case cppengine::KeyCode::D: return GLFW_KEY_D;
            case cppengine::KeyCode::E: return GLFW_KEY_E;
            case cppengine::KeyCode::F: return GLFW_KEY_F;
            case cppengine::KeyCode::G: return GLFW_KEY_G;
            case cppengine::KeyCode::H: return GLFW_KEY_H;
            case cppengine::KeyCode::I: return GLFW_KEY_I;
            case cppengine::KeyCode::J: return GLFW_KEY_J;
            case cppengine::KeyCode::K: return GLFW_KEY_K;
            case cppengine::KeyCode::L: return GLFW_KEY_L;
            case cppengine::KeyCode::M: return GLFW_KEY_M;
            case cppengine::KeyCode::N: return GLFW_KEY_N;
            case cppengine::KeyCode::O: return GLFW_KEY_O;
            case cppengine::KeyCode::P: return GLFW_KEY_P;
            case cppengine::KeyCode::Q: return GLFW_KEY_Q;
            case cppengine::KeyCode::R: return GLFW_KEY_R;
            case cppengine::KeyCode::S: return GLFW_KEY_S;
            case cppengine::KeyCode::T: return GLFW_KEY_T;
            case cppengine::KeyCode::U: return GLFW_KEY_U;
            case cppengine::KeyCode::V: return GLFW_KEY_V;
            case cppengine::KeyCode::W: return GLFW_KEY_W;
            case cppengine::KeyCode::X: return GLFW_KEY_X;
            case cppengine::KeyCode::Y: return GLFW_KEY_Y;
            case cppengine::KeyCode::Z: return GLFW_KEY_Z;
            case cppengine::KeyCode::NUM_0: return GLFW_KEY_0;
            case cppengine::KeyCode::NUM_1: return GLFW_KEY_1;
            case cppengine::KeyCode::NUM_2: return GLFW_KEY_2;
            case cppengine::KeyCode::NUM_3: return GLFW_KEY_3;
            case cppengine::KeyCode::NUM_4: return GLFW_KEY_4;
            case cppengine::KeyCode::NUM_5: return GLFW_KEY_5;
            case cppengine::KeyCode::NUM_6: return GLFW_KEY_6;
            case cppengine::KeyCode::NUM_7: return GLFW_KEY_7;
            case cppengine::KeyCode::NUM_8: return GLFW_KEY_8;
            case cppengine::KeyCode::NUM_9: return GLFW_KEY_9;
            case cppengine::KeyCode::F1: return GLFW_KEY_F1;
            case cppengine::KeyCode::F2: return GLFW_KEY_F2;
            case cppengine::KeyCode::F3: return GLFW_KEY_F3;
            case cppengine::KeyCode::F4: return GLFW_KEY_F4;
            case cppengine::KeyCode::F5: return GLFW_KEY_F5;
            case cppengine::KeyCode::F6: return GLFW_KEY_F6;
            case cppengine::KeyCode::F7: return GLFW_KEY_F7;
            case cppengine::KeyCode::F8: return GLFW_KEY_F8;
            case cppengine::KeyCode::F9: return GLFW_KEY_F9;
            case cppengine::KeyCode::F10: return GLFW_KEY_F10;
            case cppengine::KeyCode::F11: return GLFW_KEY_F11;
            case cppengine::KeyCode::F12: return GLFW_KEY_F12;
            case cppengine::KeyCode::UP_ARROW: return GLFW_KEY_UP;
            case cppengine::KeyCode::DOWN_ARROW: return GLFW_KEY_DOWN;
            case cppengine::KeyCode::LEFT_ARROW: return GLFW_KEY_LEFT;
            case cppengine::KeyCode::RIGHT_ARROW: return GLFW_KEY_RIGHT;
            case cppengine::KeyCode::LEFT_SHIFT: return GLFW_KEY_LEFT_SHIFT;
            case cppengine::KeyCode::RIGHT_SHIFT: return GLFW_KEY_RIGHT_SHIFT;
            case cppengine::KeyCode::LEFT_CONTROL: return GLFW_KEY_LEFT_CONTROL;
            case cppengine::KeyCode::RIGHT_CONTROL: return GLFW_KEY_RIGHT_CONTROL;
            case cppengine::KeyCode::LEFT_ALT: return GLFW_KEY_LEFT_ALT;
            case cppengine::KeyCode::RIGHT_ALT: return GLFW_KEY_RIGHT_ALT;
            case cppengine::KeyCode::LEFT_SUPER: return GLFW_KEY_LEFT_SUPER;
            case cppengine::KeyCode::RIGHT_SUPER: return GLFW_KEY_RIGHT_SUPER;
            case cppengine::KeyCode::SPACE: return GLFW_KEY_SPACE;
            case cppengine::KeyCode::ENTER: return GLFW_KEY_ENTER;
            case cppengine::KeyCode::ESCAPE: return GLFW_KEY_ESCAPE;
            case cppengine::KeyCode::TAB: return GLFW_KEY_TAB;
            case cppengine::KeyCode::BACKSPACE: return GLFW_KEY_BACKSPACE;
            case cppengine::KeyCode::INSERT: return GLFW_KEY_INSERT;
            case cppengine::KeyCode::DELETE: return GLFW_KEY_DELETE;
            case cppengine::KeyCode::HOME: return GLFW_KEY_HOME;
            case cppengine::KeyCode::END: return GLFW_KEY_END;
            case cppengine::KeyCode::PAGE_UP: return GLFW_KEY_PAGE_UP;
            case cppengine::KeyCode::PAGE_DOWN: return GLFW_KEY_PAGE_DOWN;
            case cppengine::KeyCode::MINUS: return GLFW_KEY_MINUS;
            case cppengine::KeyCode::EQUAL: return GLFW_KEY_EQUAL;
            case cppengine::KeyCode::LEFT_BRACKET: return GLFW_KEY_LEFT_BRACKET;
            case cppengine::KeyCode::RIGHT_BRACKET: return GLFW_KEY_RIGHT_BRACKET;
            case cppengine::KeyCode::SEMICOLON: return GLFW_KEY_SEMICOLON;
            case cppengine::KeyCode::APOSTROPHE: return GLFW_KEY_APOSTROPHE;
            case cppengine::KeyCode::COMMA: return GLFW_KEY_COMMA;
            case cppengine::KeyCode::PERIOD: return GLFW_KEY_PERIOD;
            case cppengine::KeyCode::SLASH: return GLFW_KEY_SLASH;
            case cppengine::KeyCode::BACKSLASH: return GLFW_KEY_BACKSLASH;
            case cppengine::KeyCode::GRAVE_ACCENT: return GLFW_KEY_GRAVE_ACCENT;
            case cppengine::KeyCode::KP_0: return GLFW_KEY_KP_0;
            case cppengine::KeyCode::KP_1: return GLFW_KEY_KP_1;
            case cppengine::KeyCode::KP_2: return GLFW_KEY_KP_2;
            case cppengine::KeyCode::KP_3: return GLFW_KEY_KP_3;
            case cppengine::KeyCode::KP_4: return GLFW_KEY_KP_4;
            case cppengine::KeyCode::KP_5: return GLFW_KEY_KP_5;
            case cppengine::KeyCode::KP_6: return GLFW_KEY_KP_6;
            case cppengine::KeyCode::KP_7: return GLFW_KEY_KP_7;
            case cppengine::KeyCode::KP_8: return GLFW_KEY_KP_8;
            case cppengine::KeyCode::KP_9: return GLFW_KEY_KP_9;
            case cppengine::KeyCode::KP_DECIMAL: return GLFW_KEY_KP_DECIMAL;
            case cppengine::KeyCode::KP_DIVIDE: return GLFW_KEY_KP_DIVIDE;
            case cppengine::KeyCode::KP_MULTIPLY: return GLFW_KEY_KP_MULTIPLY;
            case cppengine::KeyCode::KP_SUBTRACT: return GLFW_KEY_KP_SUBTRACT;
            case cppengine::KeyCode::KP_ADD: return GLFW_KEY_KP_ADD;
            case cppengine::KeyCode::KP_ENTER: return GLFW_KEY_KP_ENTER;
            case cppengine::KeyCode::KP_EQUAL: return GLFW_KEY_KP_EQUAL;
            case cppengine::KeyCode::CAPS_LOCK: return GLFW_KEY_CAPS_LOCK;
            case cppengine::KeyCode::NUM_LOCK: return GLFW_KEY_NUM_LOCK;
            case cppengine::KeyCode::SCROLL_LOCK: return GLFW_KEY_SCROLL_LOCK;
            case cppengine::KeyCode::PRINT_SCREEN: return GLFW_KEY_PRINT_SCREEN;
            case cppengine::KeyCode::PAUSE: return GLFW_KEY_PAUSE;
            case cppengine::KeyCode::MENU: return GLFW_KEY_MENU;
            default: return GLFW_KEY_UNKNOWN;
        }
    }
    
    int translateMouseCode(cppengine::KeyCode mouseCode) {
        switch (mouseCode) {
            case cppengine::KeyCode::MOUSE_LEFT: return GLFW_MOUSE_BUTTON_LEFT;
            case cppengine::KeyCode::MOUSE_RIGHT: return GLFW_MOUSE_BUTTON_RIGHT;
            case cppengine::KeyCode::MOUSE_MIDDLE: return GLFW_MOUSE_BUTTON_MIDDLE;
            default: return GLFW_KEY_UNKNOWN;
        }
    }

    bool isMouseCode(cppengine::KeyCode keyCode) {
        int value = static_cast<int>(keyCode);
        return value > static_cast<int>(cppengine::KeyCode::MOUSE_BUTTON_BEGIN) && value < static_cast<int>(cppengine::KeyCode::MOUSE_BUTTON_END);
    }

    bool testKey(cppengine::KeyCode keyCode, bool const *mouseStates, bool const *keyStates) {
        if (int key; isMouseCode(keyCode) && (key = translateMouseCode(keyCode)) != GLFW_KEY_UNKNOWN) {
            return mouseStates[key];
        }

        if (int key; (key = translateKeyCode(keyCode)) != GLFW_KEY_UNKNOWN && key < GLFW_KEY_LAST) {
            return keyStates[key];
        }

        return false;
    }

    void clearKeyPressedReleaseStates() {
        std::memset(keyIsPressed, 0, GLFW_KEY_LAST * sizeof(decltype(keyIsPressed[0])));
        std::memset(keyIsReleased, 0, GLFW_KEY_LAST * sizeof(decltype(keyIsReleased[0])));
        std::memset(mouseIsPressed, 0, GLFW_MOUSE_BUTTON_LAST * sizeof(decltype(mouseIsPressed[0])));
        std::memset(mouseIsReleased, 0, GLFW_MOUSE_BUTTON_LAST * sizeof(decltype(mouseIsReleased[0])));
    }

}

namespace cppengine {
    GLFWInputContext::GLFWInputContext() {
        GLFWwindow *window = GGContextManager::getWindowContext()->getWindow();
        glfwSetKeyCallback(window, &onGlfwKeyEvent);
        glfwSetMouseButtonCallback(window, &onGLFWMouseEvent);
    }

    void GLFWInputContext::clearInputs() {
        clearKeyPressedReleaseStates();
    }

    bool GLFWInputContext::isKeyDown(KeyCode keyCode) const {
        return testKey(keyCode, mouseIsDown, keyIsDown);
    }

    bool GLFWInputContext::isKeyUp(KeyCode keyCode) const {
        return !testKey(keyCode, mouseIsDown, keyIsDown);
    }

    bool GLFWInputContext::isKeyPressed(KeyCode keyCode) const {
        return testKey(keyCode, mouseIsPressed, keyIsPressed);
    }

    bool GLFWInputContext::isKeyReleased(KeyCode keyCode) const {
        return testKey(keyCode, mouseIsReleased, keyIsReleased);
    }

    GLFWInputContext::~GLFWInputContext() {

    }
}
