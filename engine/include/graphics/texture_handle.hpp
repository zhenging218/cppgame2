#ifndef TEXTURE_HANDLE_HPP
#define TEXTURE_HANDLE_HPP
#include <cstdint>
#include <string>

namespace cppengine {
    class TextureHandle {
    private:
        std::uint64_t id;

    public:
        constexpr inline TextureHandle() : id(0) {}
        constexpr inline explicit TextureHandle(std::uint64_t id_) : id(id_) {};
        TextureHandle(TextureHandle const &) = default;
        TextureHandle &operator=(TextureHandle const&other) = default;

        std::uint64_t getId() const;
        std::string const &getName() const;
        std::uint64_t getWidth() const;
        std::uint64_t getHeight() const;
    };
}

#endif