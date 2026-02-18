#include "raylib_integration.hpp"

namespace {
    cppengine::KeyCode translateKeyCode(int raylibKeyCode) {
        switch (raylibKeyCode) {
            case ::KEY_A: return cppengine::KeyCode::A;
            case ::KEY_B: return cppengine::KeyCode::B;
            case ::KEY_C: return cppengine::KeyCode::C;
            case ::KEY_D: return cppengine::KeyCode::D;
            case ::KEY_E: return cppengine::KeyCode::E;
            case ::KEY_F: return cppengine::KeyCode::F;
            case ::KEY_G: return cppengine::KeyCode::G;
            case ::KEY_H: return cppengine::KeyCode::H;
            case ::KEY_I: return cppengine::KeyCode::I;
            case ::KEY_J: return cppengine::KeyCode::J;
            case ::KEY_K: return cppengine::KeyCode::K;
            case ::KEY_L: return cppengine::KeyCode::L;
            case ::KEY_M: return cppengine::KeyCode::M;
            case KEY_N: return cppengine::KeyCode::N;
            case KEY_O: return cppengine::KeyCode::O;
            case KEY_P: return cppengine::KeyCode::P;
            case KEY_Q: return cppengine::KeyCode::Q;
            case KEY_R: return cppengine::KeyCode::R;
            case ::KEY_S: return cppengine::KeyCode::S;
            case ::KEY_T: return cppengine::KeyCode::T;
            case ::KEY_U: return cppengine::KeyCode::U;
            case ::KEY_V: return cppengine::KeyCode::V;
            case ::KEY_W: return cppengine::KeyCode::W;
            case ::KEY_X: return cppengine::KeyCode::X;
            case ::KEY_Y: return cppengine::KeyCode::Y;
            case ::KEY_Z: return cppengine::KeyCode::Z;
            case ::KEY_ZERO: return cppengine::KeyCode::NUM_0;
            case ::KEY_ONE: return cppengine::KeyCode::NUM_1;
            case ::KEY_TWO: return cppengine::KeyCode::NUM_2;
            case ::KEY_THREE: return cppengine::KeyCode::NUM_3;
            case ::KEY_FOUR: return cppengine::KeyCode::NUM_4;
            case ::KEY_FIVE: return cppengine::KeyCode::NUM_5;
            case ::KEY_SIX: return cppengine::KeyCode::NUM_6;
            case ::KEY_SEVEN: return cppengine::KeyCode::NUM_7;
            case ::KEY_EIGHT: return cppengine::KeyCode::NUM_8;
            case ::KEY_NINE: return cppengine::KeyCode::NUM_9;
            case ::KEY_F1: return cppengine::KeyCode::F1;
            case ::KEY_F2: return cppengine::KeyCode::F2;
            case ::KEY_F3: return cppengine::KeyCode::F3;
            case ::KEY_F4: return cppengine::KeyCode::F4;
            case ::KEY_F5: return cppengine::KeyCode::F5;
            case ::KEY_F6: return cppengine::KeyCode::F6;
            case ::KEY_F7: return cppengine::KeyCode::F7;
            case ::KEY_F8: return cppengine::KeyCode::F8;
            case ::KEY_F9: return cppengine::KeyCode::F9;
            case ::KEY_F10: return cppengine::KeyCode::F10;
            case ::KEY_F11: return cppengine::KeyCode::F11;
            case ::KEY_F12: return cppengine::KeyCode::F12;
            case ::KEY_UP: return cppengine::KeyCode::UP_ARROW;
            case ::KEY_DOWN: return cppengine::KeyCode::DOWN_ARROW;
            case ::KEY_LEFT: return cppengine::KeyCode::LEFT_ARROW;
            case ::KEY_RIGHT: return cppengine::KeyCode::RIGHT_ARROW;
            case ::KEY_LEFT_SHIFT: return cppengine::KeyCode::LEFT_SHIFT;
            case ::KEY_RIGHT_SHIFT: return cppengine::KeyCode::RIGHT_SHIFT;
            case ::KEY_LEFT_CONTROL: return cppengine::KeyCode::LEFT_CONTROL;
            case ::KEY_RIGHT_CONTROL: return cppengine::KeyCode::RIGHT_CONTROL;
            case ::KEY_LEFT_ALT: return cppengine::KeyCode::LEFT_ALT;
            case ::KEY_RIGHT_ALT: return cppengine::KeyCode::RIGHT_ALT;
            case ::KEY_LEFT_SUPER: return cppengine::KeyCode::LEFT_SUPER;
            case ::KEY_RIGHT_SUPER: return cppengine::KeyCode::RIGHT_SUPER;
            case ::KEY_SPACE: return cppengine::KeyCode::SPACE;
            case ::KEY_ENTER: return cppengine::KeyCode::ENTER;
            case ::KEY_ESCAPE: return cppengine::KeyCode::ESCAPE;
            case ::KEY_TAB: return cppengine::KeyCode::TAB;
            case ::KEY_BACKSPACE: return cppengine::KeyCode::BACKSPACE;
            case ::KEY_INSERT: return cppengine::KeyCode::INSERT;
            case ::KEY_DELETE: return cppengine::KeyCode::DELETE;
            case ::KEY_HOME: return cppengine::KeyCode::HOME;
            case ::KEY_END: return cppengine::KeyCode::END;
            case ::KEY_PAGE_UP: return cppengine::KeyCode::PAGE_UP;
            case ::KEY_PAGE_DOWN: return cppengine::KeyCode::PAGE_DOWN;
            case ::KEY_MINUS: return cppengine::KeyCode::MINUS;
            case ::KEY_EQUAL: return cppengine::KeyCode::EQUAL;
            case ::KEY_LEFT_BRACKET: return cppengine::KeyCode::LEFT_BRACKET;
            case ::KEY_RIGHT_BRACKET: return cppengine::KeyCode::RIGHT_BRACKET;
            case ::KEY_SEMICOLON: return cppengine::KeyCode::SEMICOLON;
            case ::KEY_APOSTROPHE: return cppengine::KeyCode::APOSTROPHE;
            case ::KEY_COMMA: return cppengine::KeyCode::COMMA;
            case ::KEY_PERIOD: return cppengine::KeyCode::PERIOD;
            case ::KEY_SLASH: return cppengine::KeyCode::SLASH;
            case ::KEY_BACKSLASH: return cppengine::KeyCode::BACKSLASH;
            case ::KEY_GRAVE: return cppengine::KeyCode::GRAVE_ACCENT;
            case ::KEY_KP_0: return cppengine::KeyCode::KP_0;
            case ::KEY_KP_1: return cppengine::KeyCode::KP_1;
            case ::KEY_KP_2: return cppengine::KeyCode::KP_2;
            case ::KEY_KP_3: return cppengine::KeyCode::KP_3;
            case ::KEY_KP_4: return cppengine::KeyCode::KP_4;
            case ::KEY_KP_5: return cppengine::KeyCode::KP_5;
            case ::KEY_KP_6: return cppengine::KeyCode::KP_6;
            case ::KEY_KP_7: return cppengine::KeyCode::KP_7;
            case ::KEY_KP_8: return cppengine::KeyCode::KP_8;
            case ::KEY_KP_9: return cppengine::KeyCode::KP_9;
            case ::KEY_KP_DECIMAL: return cppengine::KeyCode::KP_DECIMAL;
            case ::KEY_KP_DIVIDE: return cppengine::KeyCode::KP_DIVIDE;
            case ::KEY_KP_MULTIPLY: return cppengine::KeyCode::KP_MULTIPLY;
            case ::KEY_KP_SUBTRACT: return cppengine::KeyCode::KP_SUBTRACT;
            case ::KEY_KP_ADD: return cppengine::KeyCode::KP_ADD;
            case ::KEY_KP_ENTER: return cppengine::KeyCode::KP_ENTER;
            case ::KEY_KP_EQUAL: return cppengine::KeyCode::KP_EQUAL;
            case ::KEY_CAPS_LOCK: return cppengine::KeyCode::CAPS_LOCK;
            case ::KEY_NUM_LOCK: return cppengine::KeyCode::NUM_LOCK;
            case ::KEY_SCROLL_LOCK: return cppengine::KeyCode::SCROLL_LOCK;
            case ::KEY_PRINT_SCREEN: return cppengine::KeyCode::PRINT_SCREEN;
            case ::KEY_PAUSE: return cppengine::KeyCode::PAUSE;
            case ::KEY_MENU: return cppengine::KeyCode::MENU;
            case ::MOUSE_BUTTON_LEFT: return cppengine::KeyCode::MOUSE_LEFT;
            case ::MOUSE_BUTTON_RIGHT: return cppengine::KeyCode::MOUSE_RIGHT;
            case ::MOUSE_BUTTON_MIDDLE: return cppengine::KeyCode::MOUSE_MIDDLE;
            default: throw std::invalid_argument("");
        }
    }

    int translateKeyCode(cppengine::KeyCode keyCode) {
        switch (keyCode) {
            case cppengine::KeyCode::A: return KEY_A;
            case cppengine::KeyCode::B: return KEY_B;
            case cppengine::KeyCode::C: return KEY_C;
            case cppengine::KeyCode::D: return KEY_D;
            case cppengine::KeyCode::E: return KEY_E;
            case cppengine::KeyCode::F: return KEY_F;
            case cppengine::KeyCode::G: return KEY_G;
            case cppengine::KeyCode::H: return KEY_H;
            case cppengine::KeyCode::I: return KEY_I;
            case cppengine::KeyCode::J: return KEY_J;
            case cppengine::KeyCode::K: return KEY_K;
            case cppengine::KeyCode::L: return KEY_L;
            case cppengine::KeyCode::M: return KEY_M;
            case cppengine::KeyCode::N: return KEY_N;
            case cppengine::KeyCode::O: return KEY_O;
            case cppengine::KeyCode::P: return KEY_P;
            case cppengine::KeyCode::Q: return KEY_Q;
            case cppengine::KeyCode::R: return KEY_R;
            case cppengine::KeyCode::S: return KEY_S;
            case cppengine::KeyCode::T: return KEY_T;
            case cppengine::KeyCode::U: return KEY_U;
            case cppengine::KeyCode::V: return KEY_V;
            case cppengine::KeyCode::W: return KEY_W;
            case cppengine::KeyCode::X: return KEY_X;
            case cppengine::KeyCode::Y: return KEY_Y;
            case cppengine::KeyCode::Z: return KEY_Z;
            case cppengine::KeyCode::NUM_0: return KEY_ZERO;
            case cppengine::KeyCode::NUM_1: return KEY_ONE;
            case cppengine::KeyCode::NUM_2: return KEY_TWO;
            case cppengine::KeyCode::NUM_3: return KEY_THREE;
            case cppengine::KeyCode::NUM_4: return KEY_FOUR;
            case cppengine::KeyCode::NUM_5: return KEY_FIVE;
            case cppengine::KeyCode::NUM_6: return KEY_SIX;
            case cppengine::KeyCode::NUM_7: return KEY_SEVEN;
            case cppengine::KeyCode::NUM_8: return KEY_EIGHT;
            case cppengine::KeyCode::NUM_9: return KEY_NINE;
            case cppengine::KeyCode::F1: return KEY_F1;
            case cppengine::KeyCode::F2: return KEY_F2;
            case cppengine::KeyCode::F3: return KEY_F3;
            case cppengine::KeyCode::F4: return KEY_F4;
            case cppengine::KeyCode::F5: return KEY_F5;
            case cppengine::KeyCode::F6: return KEY_F6;
            case cppengine::KeyCode::F7: return KEY_F7;
            case cppengine::KeyCode::F8: return KEY_F8;
            case cppengine::KeyCode::F9: return KEY_F9;
            case cppengine::KeyCode::F10: return KEY_F10;
            case cppengine::KeyCode::F11: return KEY_F11;
            case cppengine::KeyCode::F12: return KEY_F12;
            case cppengine::KeyCode::UP_ARROW: return KEY_UP;
            case cppengine::KeyCode::DOWN_ARROW: return KEY_DOWN;
            case cppengine::KeyCode::LEFT_ARROW: return KEY_LEFT;
            case cppengine::KeyCode::RIGHT_ARROW: return KEY_RIGHT;
            case cppengine::KeyCode::LEFT_SHIFT: return KEY_LEFT_SHIFT;
            case cppengine::KeyCode::RIGHT_SHIFT: return KEY_RIGHT_SHIFT;
            case cppengine::KeyCode::LEFT_CONTROL: return KEY_LEFT_CONTROL;
            case cppengine::KeyCode::RIGHT_CONTROL: return KEY_RIGHT_CONTROL;
            case cppengine::KeyCode::LEFT_ALT: return KEY_LEFT_ALT;
            case cppengine::KeyCode::RIGHT_ALT: return KEY_RIGHT_ALT;
            case cppengine::KeyCode::LEFT_SUPER: return KEY_LEFT_SUPER;
            case cppengine::KeyCode::RIGHT_SUPER: return KEY_RIGHT_SUPER;
            case cppengine::KeyCode::SPACE: return KEY_SPACE;
            case cppengine::KeyCode::ENTER: return KEY_ENTER;
            case cppengine::KeyCode::ESCAPE: return KEY_ESCAPE;
            case cppengine::KeyCode::TAB: return KEY_TAB;
            case cppengine::KeyCode::BACKSPACE: return KEY_BACKSPACE;
            case cppengine::KeyCode::INSERT: return KEY_INSERT;
            case cppengine::KeyCode::DELETE: return KEY_DELETE;
            case cppengine::KeyCode::HOME: return KEY_HOME;
            case cppengine::KeyCode::END: return KEY_END;
            case cppengine::KeyCode::PAGE_UP: return KEY_PAGE_UP;
            case cppengine::KeyCode::PAGE_DOWN: return KEY_PAGE_DOWN;
            case cppengine::KeyCode::MINUS: return KEY_MINUS;
            case cppengine::KeyCode::EQUAL: return KEY_EQUAL;
            case cppengine::KeyCode::LEFT_BRACKET: return KEY_LEFT_BRACKET;
            case cppengine::KeyCode::RIGHT_BRACKET: return KEY_RIGHT_BRACKET;
            case cppengine::KeyCode::SEMICOLON: return KEY_SEMICOLON;
            case cppengine::KeyCode::APOSTROPHE: return KEY_APOSTROPHE;
            case cppengine::KeyCode::COMMA: return KEY_COMMA;
            case cppengine::KeyCode::PERIOD: return KEY_PERIOD;
            case cppengine::KeyCode::SLASH: return KEY_SLASH;
            case cppengine::KeyCode::BACKSLASH: return KEY_BACKSLASH;
            case cppengine::KeyCode::GRAVE_ACCENT: return KEY_GRAVE;
            case cppengine::KeyCode::KP_0: return KEY_KP_0;
            case cppengine::KeyCode::KP_1: return KEY_KP_1;
            case cppengine::KeyCode::KP_2: return KEY_KP_2;
            case cppengine::KeyCode::KP_3: return KEY_KP_3;
            case cppengine::KeyCode::KP_4: return KEY_KP_4;
            case cppengine::KeyCode::KP_5: return KEY_KP_5;
            case cppengine::KeyCode::KP_6: return KEY_KP_6;
            case cppengine::KeyCode::KP_7: return KEY_KP_7;
            case cppengine::KeyCode::KP_8: return KEY_KP_8;
            case cppengine::KeyCode::KP_9: return KEY_KP_9;
            case cppengine::KeyCode::KP_DECIMAL: return KEY_KP_DECIMAL;
            case cppengine::KeyCode::KP_DIVIDE: return KEY_KP_DIVIDE;
            case cppengine::KeyCode::KP_MULTIPLY: return KEY_KP_MULTIPLY;
            case cppengine::KeyCode::KP_SUBTRACT: return KEY_KP_SUBTRACT;
            case cppengine::KeyCode::KP_ADD: return KEY_KP_ADD;
            case cppengine::KeyCode::KP_ENTER: return KEY_KP_ENTER;
            case cppengine::KeyCode::KP_EQUAL: return KEY_KP_EQUAL;
            case cppengine::KeyCode::CAPS_LOCK: return KEY_CAPS_LOCK;
            case cppengine::KeyCode::NUM_LOCK: return KEY_NUM_LOCK;
            case cppengine::KeyCode::SCROLL_LOCK: return KEY_SCROLL_LOCK;
            case cppengine::KeyCode::PRINT_SCREEN: return KEY_PRINT_SCREEN;
            case cppengine::KeyCode::PAUSE: return KEY_PAUSE;
            case cppengine::KeyCode::MENU: return KEY_MENU;
            case cppengine::KeyCode::MOUSE_LEFT: return MOUSE_BUTTON_LEFT;
            case cppengine::KeyCode::MOUSE_RIGHT: return MOUSE_BUTTON_RIGHT;
            case cppengine::KeyCode::MOUSE_MIDDLE: return MOUSE_BUTTON_MIDDLE;
            default: throw std::invalid_argument("");
        }
    }
}

namespace cppengine {
    bool RaylibInputContext::isKeyUp(KeyCode keyCode) const {
        return IsKeyUp(translateKeyCode(keyCode));
    }

    bool RaylibInputContext::isKeyDown(KeyCode keyCode) const {
        return IsKeyDown(translateKeyCode(keyCode));
    }

    bool RaylibInputContext::isKeyPressed(KeyCode keyCode) const {
        return IsKeyPressed(translateKeyCode(keyCode));
    }

    bool RaylibInputContext::isKeyReleased(KeyCode keyCode) const {
        return IsKeyReleased(translateKeyCode(keyCode));
    }
}
