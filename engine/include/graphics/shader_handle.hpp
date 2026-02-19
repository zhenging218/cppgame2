#ifndef SHADER_HANDLE_HPP
#define SHADER_HANDLE_HPP
#include <cstdint>

namespace cppengine {
    class ShaderHandle {
    private:
        std::uint64_t id;

    public:
        constexpr inline ShaderHandle() : id(0) {}
        constexpr inline explicit ShaderHandle(std::uint64_t id_) : id(id_) {}

        std::uint64_t getId() const;
    };
}

#endif