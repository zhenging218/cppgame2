#include "engine.hpp"
#include "raylib_integration.hpp"

#include <raylib.h>

namespace cppengine {
    void RaylibWindowContext::createWindow(int width, int height, const std::string &title) {
        InitWindow(width, height, title.c_str());
    }

    bool RaylibWindowContext::windowShouldClose() const {
        return WindowShouldClose();
    }

    void RaylibWindowContext::beginFrame() {
        BeginDrawing();
    }

    void RaylibWindowContext::endFrame() {
        EndDrawing();
    }

    int RaylibWindowContext::getWidth() const {
        return GetScreenWidth();
    }

    int RaylibWindowContext::getHeight() const {
        return GetScreenHeight();
    }

    void RaylibWindowContext::closeWindow() {
        CloseWindow();
    }
}
