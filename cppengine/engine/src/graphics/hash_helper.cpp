//
// Created by Admin on 5/11/2026.
//

#include "graphics/graphics.hpp"

namespace cppengine::HashHelper {
    size_t StringHash::operator()(const char *txt) const {
        return std::hash<std::string_view>{}(txt);
    }

    size_t StringHash::operator()(std::string_view txt) const {
        return std::hash<std::string_view>{}(txt);
    }

    size_t StringHash::operator()(const std::string &txt) const {
        return std::hash<std::string>{}(txt);
    }
}