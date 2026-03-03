#ifndef GG_CONTEXT_MANAGER_HPP
#define GG_CONTEXT_MANAGER_HPP
#include "glfw_window_context.hpp"
#include "glfw_input_context.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    class GGContextManager {
    private:
        ObjectHandle<GLFWWindowContext> windowContext;
        ObjectHandle<GLFWInputContext> inputContext;

    public:
        GGContextManager() = default;
        GGContextManager(GGContextManager const &) = delete;
        GGContextManager &operator=(GGContextManager const &) = delete;

        static GGContextManager &getInstance();
        static ObjectHandle<GLFWWindowContext> getWindowContext();
        static ObjectHandle<GLFWInputContext> getInputContext();
    };
}

#endif