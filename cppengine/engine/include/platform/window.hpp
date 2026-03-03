#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>

#include "memory/object_handle.hpp"

namespace cppengine {
    class WindowContext;

    class Window {
    private:
        static ObjectHandle<WindowContext> createContext();
        ObjectHandle<WindowContext> context;
    public:
        Window();
        Window(Window const &) = delete;
        Window(Window &&) = delete;
        Window &operator=(Window const &) = delete;
        Window &operator=(Window &&) = delete;

        void initialise();
        void createWindow(int width, int height, std::string const &title);
        bool windowShouldClose() const;
        void beginFrame();
        void endFrame();
        void closeWindow();
        void shutdown();

        int getWidth() const;
        int getHeight() const;

        static Window &getInstance();
    };
}

#endif