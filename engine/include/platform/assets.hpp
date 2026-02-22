#ifndef ASSETS_HPP
#define ASSETS_HPP
#include <string>
#include <utility>

namespace cppengine {
    class Assets {
    private:

    public:
        Assets();
        Assets(Assets const &) = delete;
        Assets &operator=(Assets const &) = delete;

        static Assets &getinstance();

        static std::string getDirectory(std::string_view root, std::string_view name);

    };
}

#endif