#ifndef RAYLIB_HASH_HELPER_HPP
#define RAYLIB_HASH_HELPER_HPP
#include <string_view>

namespace cppengine {
    namespace HashHelper {
        constexpr std::uint64_t fnv1a_64(std::string_view str) {
            uint64_t hash = 14695981039346656037ULL;
            for (char c : str) {
                hash ^= static_cast<uint64_t>(c);
                hash *= 1099511628211ULL;
            }
            return hash;
        }
    }

}

#endif