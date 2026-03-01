#include <cstring>

#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    using namespace cppengine;
    
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

    int translateKeyCode(KeyCode keyCode) {
        switch (keyCode) {
            case KeyCode::A: return GLFW_KEY_A;
            case KeyCode::B: return GLFW_KEY_B;
            case KeyCode::C: return GLFW_KEY_C;
            case KeyCode::D: return GLFW_KEY_D;
            case KeyCode::E: return GLFW_KEY_E;
            case KeyCode::F: return GLFW_KEY_F;
            case KeyCode::G: return GLFW_KEY_G;
            case KeyCode::H: return GLFW_KEY_H;
            case KeyCode::I: return GLFW_KEY_I;
            case KeyCode::J: return GLFW_KEY_J;
            case KeyCode::K: return GLFW_KEY_K;
            case KeyCode::L: return GLFW_KEY_L;
            case KeyCode::M: return GLFW_KEY_M;
            case KeyCode::N: return GLFW_KEY_N;
            case KeyCode::O: return GLFW_KEY_O;
            case KeyCode::P: return GLFW_KEY_P;
            case KeyCode::Q: return GLFW_KEY_Q;
            case KeyCode::R: return GLFW_KEY_R;
            case KeyCode::S: return GLFW_KEY_S;
            case KeyCode::T: return GLFW_KEY_T;
            case KeyCode::U: return GLFW_KEY_U;
            case KeyCode::V: return GLFW_KEY_V;
            case KeyCode::W: return GLFW_KEY_W;
            case KeyCode::X: return GLFW_KEY_X;
            case KeyCode::Y: return GLFW_KEY_Y;
            case KeyCode::Z: return GLFW_KEY_Z;
            case KeyCode::NUM_0: return GLFW_KEY_0;
            case KeyCode::NUM_1: return GLFW_KEY_1;
            case KeyCode::NUM_2: return GLFW_KEY_2;
            case KeyCode::NUM_3: return GLFW_KEY_3;
            case KeyCode::NUM_4: return GLFW_KEY_4;
            case KeyCode::NUM_5: return GLFW_KEY_5;
            case KeyCode::NUM_6: return GLFW_KEY_6;
            case KeyCode::NUM_7: return GLFW_KEY_7;
            case KeyCode::NUM_8: return GLFW_KEY_8;
            case KeyCode::NUM_9: return GLFW_KEY_9;
            case KeyCode::F1: return GLFW_KEY_F1;
            case KeyCode::F2: return GLFW_KEY_F2;
            case KeyCode::F3: return GLFW_KEY_F3;
            case KeyCode::F4: return GLFW_KEY_F4;
            case KeyCode::F5: return GLFW_KEY_F5;
            case KeyCode::F6: return GLFW_KEY_F6;
            case KeyCode::F7: return GLFW_KEY_F7;
            case KeyCode::F8: return GLFW_KEY_F8;
            case KeyCode::F9: return GLFW_KEY_F9;
            case KeyCode::F10: return GLFW_KEY_F10;
            case KeyCode::F11: return GLFW_KEY_F11;
            case KeyCode::F12: return GLFW_KEY_F12;
            case KeyCode::UP_ARROW: return GLFW_KEY_UP;
            case KeyCode::DOWN_ARROW: return GLFW_KEY_DOWN;
            case KeyCode::LEFT_ARROW: return GLFW_KEY_LEFT;
            case KeyCode::RIGHT_ARROW: return GLFW_KEY_RIGHT;
            case KeyCode::LEFT_SHIFT: return GLFW_KEY_LEFT_SHIFT;
            case KeyCode::RIGHT_SHIFT: return GLFW_KEY_RIGHT_SHIFT;
            case KeyCode::LEFT_CONTROL: return GLFW_KEY_LEFT_CONTROL;
            case KeyCode::RIGHT_CONTROL: return GLFW_KEY_RIGHT_CONTROL;
            case KeyCode::LEFT_ALT: return GLFW_KEY_LEFT_ALT;
            case KeyCode::RIGHT_ALT: return GLFW_KEY_RIGHT_ALT;
            case KeyCode::LEFT_SUPER: return GLFW_KEY_LEFT_SUPER;
            case KeyCode::RIGHT_SUPER: return GLFW_KEY_RIGHT_SUPER;
            case KeyCode::SPACE: return GLFW_KEY_SPACE;
            case KeyCode::ENTER: return GLFW_KEY_ENTER;
            case KeyCode::ESCAPE: return GLFW_KEY_ESCAPE;
            case KeyCode::TAB: return GLFW_KEY_TAB;
            case KeyCode::BACKSPACE: return GLFW_KEY_BACKSPACE;
            case KeyCode::INSERT: return GLFW_KEY_INSERT;
            case KeyCode::DELETE: return GLFW_KEY_DELETE;
            case KeyCode::HOME: return GLFW_KEY_HOME;
            case KeyCode::END: return GLFW_KEY_END;
            case KeyCode::PAGE_UP: return GLFW_KEY_PAGE_UP;
            case KeyCode::PAGE_DOWN: return GLFW_KEY_PAGE_DOWN;
            case KeyCode::MINUS: return GLFW_KEY_MINUS;
            case KeyCode::EQUAL: return GLFW_KEY_EQUAL;
            case KeyCode::LEFT_BRACKET: return GLFW_KEY_LEFT_BRACKET;
            case KeyCode::RIGHT_BRACKET: return GLFW_KEY_RIGHT_BRACKET;
            case KeyCode::SEMICOLON: return GLFW_KEY_SEMICOLON;
            case KeyCode::APOSTROPHE: return GLFW_KEY_APOSTROPHE;
            case KeyCode::COMMA: return GLFW_KEY_COMMA;
            case KeyCode::PERIOD: return GLFW_KEY_PERIOD;
            case KeyCode::SLASH: return GLFW_KEY_SLASH;
            case KeyCode::BACKSLASH: return GLFW_KEY_BACKSLASH;
            case KeyCode::GRAVE_ACCENT: return GLFW_KEY_GRAVE_ACCENT;
            case KeyCode::KP_0: return GLFW_KEY_KP_0;
            case KeyCode::KP_1: return GLFW_KEY_KP_1;
            case KeyCode::KP_2: return GLFW_KEY_KP_2;
            case KeyCode::KP_3: return GLFW_KEY_KP_3;
            case KeyCode::KP_4: return GLFW_KEY_KP_4;
            case KeyCode::KP_5: return GLFW_KEY_KP_5;
            case KeyCode::KP_6: return GLFW_KEY_KP_6;
            case KeyCode::KP_7: return GLFW_KEY_KP_7;
            case KeyCode::KP_8: return GLFW_KEY_KP_8;
            case KeyCode::KP_9: return GLFW_KEY_KP_9;
            case KeyCode::KP_DECIMAL: return GLFW_KEY_KP_DECIMAL;
            case KeyCode::KP_DIVIDE: return GLFW_KEY_KP_DIVIDE;
            case KeyCode::KP_MULTIPLY: return GLFW_KEY_KP_MULTIPLY;
            case KeyCode::KP_SUBTRACT: return GLFW_KEY_KP_SUBTRACT;
            case KeyCode::KP_ADD: return GLFW_KEY_KP_ADD;
            case KeyCode::KP_ENTER: return GLFW_KEY_KP_ENTER;
            case KeyCode::KP_EQUAL: return GLFW_KEY_KP_EQUAL;
            case KeyCode::CAPS_LOCK: return GLFW_KEY_CAPS_LOCK;
            case KeyCode::NUM_LOCK: return GLFW_KEY_NUM_LOCK;
            case KeyCode::SCROLL_LOCK: return GLFW_KEY_SCROLL_LOCK;
            case KeyCode::PRINT_SCREEN: return GLFW_KEY_PRINT_SCREEN;
            case KeyCode::PAUSE: return GLFW_KEY_PAUSE;
            case KeyCode::MENU: return GLFW_KEY_MENU;
            default: return GLFW_KEY_UNKNOWN;
        }
    }
    
    int translateMouseCode(KeyCode mouseCode) {
        switch (mouseCode) {
            case KeyCode::MOUSE_LEFT: return GLFW_MOUSE_BUTTON_LEFT;
            case KeyCode::MOUSE_RIGHT: return GLFW_MOUSE_BUTTON_RIGHT;
            case KeyCode::MOUSE_MIDDLE: return GLFW_MOUSE_BUTTON_MIDDLE;
            default: return GLFW_KEY_UNKNOWN;
        }
    }

    bool isMouseCode(KeyCode keyCode) {
        int value = static_cast<int>(keyCode);
        return value > static_cast<int>(KeyCode::MOUSE_BUTTON_BEGIN) && value < static_cast<int>(KeyCode::MOUSE_BUTTON_END);
    }

    bool testKey(KeyCode keyCode, bool const *mouseStates, bool const *keyStates) {
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
