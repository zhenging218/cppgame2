#ifndef STRING_LITERAL_HPP
#define STRING_LITERAL_HPP

#include <algorithm>
#include <cstdint>

namespace cppengine {
  template <std::size_t N>
  struct StringLiteral {
    char literal[N];

    constexpr StringLiteral(char const (&literal_)[N]) { std::copy_n(literal_, N, literal); }

    constexpr operator char const *() const { return literal; }
  };

  template <std::size_t N>
  constexpr std::size_t getStringLiteralLength(char const (&literal)[N]) noexcept {
    return N;
  }
}

#endif