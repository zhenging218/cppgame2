#ifndef ASSETS_HPP
#define ASSETS_HPP
#include <string>
#include <utility>
#include <fstream>

#include "image_loader_context.hpp"

namespace cppengine {
    class Assets {
    private:

        ObjectHandle<ImageLoaderContext> imageLoaderContext;

        static ObjectHandle<ImageLoaderContext> createImageLoaderContext();

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