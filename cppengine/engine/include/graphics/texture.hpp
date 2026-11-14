#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <cstdint>
#include <string>

#include "reflection/type_descriptor.hpp"

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

        ENABLE_REFLECTION();
    };
}

DECL_TYPE_DESCRIPTOR(cppengine::Texture);

DECL_TYPE_MEMBERS(cppengine::Texture)
    DECL_TYPE_MEMBER_FIELD(id)
END_DECL_TYPE_MEMBERS();

#endif