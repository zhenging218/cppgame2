#ifndef RAYLIB_WINDOW_CONTEXT_HPP
#define RAYLIB_WINDOW_CONTEXT_HPP

#include "integration/window_context.hpp"

namespace cppengine {
    class RaylibWindowContext : public WindowContext {
    private:

    public:
        void createWindow(int width, int height, const std::string &title) override;
        bool windowShouldClose() const override;

        void beginFrame() override;
        void endFrame() override;

        void closeWindow() override;

        ~RaylibWindowContext() override = default;
    };
}

#endif