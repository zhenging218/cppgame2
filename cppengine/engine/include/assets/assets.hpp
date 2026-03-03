#ifndef ASSETS_HPP
#define ASSETS_HPP
#include <string>
#include <utility>
#include <fstream>

#include "memory/object_handle.hpp"
#include "image_context.hpp"

namespace cppengine {
    class Assets {
    private:

        ObjectHandle<ImageContext> imageContext;

        static ObjectHandle<ImageContext> createImageContext();

    public:
        Assets();
        Assets(Assets const &) = delete;
        Assets &operator=(Assets const &) = delete;

        static Assets &getInstance();

        static std::string getDirectory(std::string_view root, std::string_view name);
        static std::ifstream openFile(std::string_view filename);

    };
}

#endif