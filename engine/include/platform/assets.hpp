#ifndef ASSETS_HPP
#define ASSETS_HPP
#include <string>
#include <utility>
#include <fstream>

namespace cppengine {
    class Assets {
    private:

    public:
        Assets();
        Assets(Assets const &) = delete;
        Assets &operator=(Assets const &) = delete;

        static Assets &getinstance();

        static std::string getDirectory(std::string_view root, std::string_view name);
        static std::ifstream openFile(std::string_view filename);

    };
}

#endif