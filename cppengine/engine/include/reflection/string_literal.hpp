#ifndef STRING_LITERAL_HPP
#define STRING_LITERAL_HPP

#include <algorithm>
#include <iterator>
#include <cstdint>

namespace cppengine {
  template <std::size_t N> requires (N > 0)
  struct StringLiteral {
    char literal[N];

    constexpr StringLiteral() : literal{} {}
    constexpr StringLiteral(char const (&literal_)[N]) : StringLiteral() { std::copy_n(literal_, N, literal); }

    // range specification
    using value_type = std::remove_cvref_t<decltype(*literal)>;
    using size_type = decltype(N);
    using difference_type = std::ptrdiff_t;
    using reference = value_type &;
    using const_reference = value_type const &;
    using pointer = value_type *;
    using const_pointer = value_type const *;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    [[nodiscard]] constexpr iterator begin() noexcept { return literal; }
    [[nodiscard]] constexpr const_iterator begin() const noexcept { return literal; }
    [[nodiscard]] constexpr iterator end() noexcept { return literal + N - 1; }
    [[nodiscard]] constexpr const_iterator end() const noexcept { return literal + N - 1; }

    [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }
    [[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }
    [[nodiscard]] constexpr pointer data() noexcept { return literal; }
    [[nodiscard]] constexpr const_pointer data() const noexcept { return literal; }

    [[nodiscard]] static constexpr size_type size() noexcept { return N - 1; }
    [[nodiscard]] static constexpr bool empty() noexcept { return N == 1; }

    [[nodiscard]] constexpr reference operator[](size_type i) noexcept { return literal[i]; }
    [[nodiscard]] constexpr const_reference operator[](size_type i) const noexcept { return literal[i]; }

    [[nodiscard]] constexpr reference front() noexcept { return literal[0]; }
    [[nodiscard]] constexpr const_reference front() const noexcept { return literal[0]; }
    [[nodiscard]] constexpr reference back() noexcept { return literal[N - 2]; }
    [[nodiscard]] constexpr const_reference back() const noexcept { return literal[N - 2]; }
  };

  template <std::size_t ... N>
  constexpr auto concatLiterals(StringLiteral<N> const &...literals) {
    constexpr auto size = (N + ...) - sizeof...(N) + 1;

    StringLiteral<size> literal;

    std::size_t pos = 0;
    auto append = [&](char const *str, std::size_t length) {
      std::size_t i = 0;
      while (i < length - 1) {
        literal[pos++] = str[i++];
      }
    };

    (append(literals.data(), N), ...);

    literal[pos] = '\0';

    return literal;
  }
}

#endif