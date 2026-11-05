//
// Created by Admin on 5/11/2026.
//

#ifndef CPPGAME_GLAD_RENDERER_HELPER_HPP
#define CPPGAME_GLAD_RENDERER_HELPER_HPP
#include <string_view>

namespace cppengine {
    namespace GladRendererHelper {
        struct StringHash {
            using is_transparent = void;
            [[nodiscard]] size_t operator()(const char *txt) const;
            [[nodiscard]] size_t operator()(std::string_view txt) const;
            [[nodiscard]] size_t operator()(const std::string &txt) const;
        };
    }
}

#endif //CPPGAME_GLAD_RENDERER_HELPER_HPP
