#ifndef WINDOW_CONTEXT_HPP
#define WINDOW_CONTEXT_HPP
#include <string>

namespace cppengine {
    class WindowContext {
    private:

    public:
        virtual void createWindow(int width, int height, std::string const &title) = 0;
        virtual bool windowShouldClose() const = 0;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        virtual void closeWindow() = 0;
        virtual ~WindowContext() = 0;
    };

    inline WindowContext::~WindowContext() = default;
}

#endif