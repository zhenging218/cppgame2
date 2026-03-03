#ifndef INPUT_HPP
#define INPUT_HPP

#include "enum_key_code.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    class InputContext;

    class Input {
    private:

        ObjectHandle<InputContext> context;
        static ObjectHandle<InputContext> createContext();

    public:

        static Input &getInstance();

        void initialise();
        void shutdown();

        void getInputs();

        static bool isKeyDown(KeyCode keyCode);
        static bool isKeyUp(KeyCode keyCode);
        static bool isKeyPressed(KeyCode keyCode);
        static bool isKeyReleased(KeyCode keyCode);
    };
}

#endif