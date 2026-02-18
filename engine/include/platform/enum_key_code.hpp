#ifndef ENUM_KEY_CODE_HPP
#define ENUM_KEY_CODE_HPP

namespace cppengine {
    enum class KeyCode {
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        // Number keys
        NUM_0 = 48,
        NUM_1 = 49,
        NUM_2 = 50,
        NUM_3 = 51,
        NUM_4 = 52,
        NUM_5 = 53,
        NUM_6 = 54,
        NUM_7 = 55,
        NUM_8 = 56,
        NUM_9 = 57,

        // Function keys
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,

        // Arrow keys
        UP_ARROW = 265,
        DOWN_ARROW = 264,
        LEFT_ARROW = 263,
        RIGHT_ARROW = 262,

        // Modifier keys
        LEFT_SHIFT = 340,
        RIGHT_SHIFT = 344,
        LEFT_CONTROL = 341,
        RIGHT_CONTROL = 345,
        LEFT_ALT = 342,
        RIGHT_ALT = 346,
        LEFT_SUPER = 343,
        RIGHT_SUPER = 347,

        // Special keys
        SPACE = 32,
        ENTER = 257,
        ESCAPE = 256,
        TAB = 258,
        BACKSPACE = 259,
        INSERT = 260,
        DELETE = 261,
        HOME = 268,
        END = 269,
        PAGE_UP = 266,
        PAGE_DOWN = 267,

        // Punctuation and symbols
        MINUS = 45,
        EQUAL = 61,
        LEFT_BRACKET = 91,
        RIGHT_BRACKET = 93,
        SEMICOLON = 59,
        APOSTROPHE = 39,
        COMMA = 44,
        PERIOD = 46,
        SLASH = 47,
        BACKSLASH = 92,
        GRAVE_ACCENT = 96,

        // Keypad keys
        KP_0 = 320,
        KP_1 = 321,
        KP_2 = 322,
        KP_3 = 323,
        KP_4 = 324,
        KP_5 = 325,
        KP_6 = 326,
        KP_7 = 327,
        KP_8 = 328,
        KP_9 = 329,
        KP_DECIMAL = 330,
        KP_DIVIDE = 331,
        KP_MULTIPLY = 332,
        KP_SUBTRACT = 333,
        KP_ADD = 334,
        KP_ENTER = 335,
        KP_EQUAL = 336,

        // Lock keys
        CAPS_LOCK = 280,
        NUM_LOCK = 282,
        SCROLL_LOCK = 281,

        // Miscellaneous
        PRINT_SCREEN = 283,
        PAUSE = 284,
        MENU = 348,

        MOUSE_LEFT  = 0,
        MOUSE_RIGHT = 1,
        MOUSE_MIDDLE = 2
    };
}

#endif