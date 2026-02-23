#ifndef GG_CONTEXT_MANAGER_HPP
#define GG_CONTEXT_MANAGER_HPP
#include "glfw_window_context.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    class GGContextManager {
    private:
        ObjectHandle<GLFWWindowContext> windowContext;

    public:
        GGContextManager();

        static GGContextManager &getInstance();
        static ObjectHandle<GLFWWindowContext> getWindowContext();
    };
}

#endif