#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <cstdint>
#include <string>

namespace cppengine {
    class Texture {
    private:
        std::uint64_t id;

    public:
        constexpr inline Texture() : id(0) {}
        constexpr inline explicit Texture(std::uint64_t id_) : id(id_) {};
        Texture(Texture const &) = default;
        Texture &operator=(Texture const&other) = default;

        std::uint64_t getId() const;
        std::string const &getName() const;
        std::uint64_t getWidth() const;
        std::uint64_t getHeight() const;
    };
}

#endif