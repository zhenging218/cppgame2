#include "engine.hpp"
#include <filesystem>

namespace cppengine {
    Assets::Assets() {

    }

    Assets &Assets::getinstance() {
        static Assets instance;
        return instance;
    }

    std::string Assets::getDirectory(std::string_view root, std::string_view name) {
        std::filesystem::path path = "./assets";
        return (path / root / name).string();
    }
}
