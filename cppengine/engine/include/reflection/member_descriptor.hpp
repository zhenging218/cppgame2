//
// Created by Admin on 14/11/2026.
//

#ifndef CPPGAME_MEMBER_DESCRIPTOR_HPP
#define CPPGAME_MEMBER_DESCRIPTOR_HPP

#include "string_literal.hpp"
#include <type_traits>
#include <functional>
#include <concepts>

namespace cppengine {
    template <typename T, StringLiteral name, typename U, U T::* member = nullptr, auto getter = nullptr, auto setter = nullptr>
    struct MemberDescriptor {
        using owner_type = T;
        using field_type = U;

        static constexpr bool hasMember = member != nullptr;
        static constexpr bool hasGetter = !std::is_null_pointer_v<decltype(getter)>;
        static constexpr bool hasSetter = !std::is_null_pointer_v<decltype(setter)>;

        static_assert((hasMember && !hasGetter && !hasSetter) || (!hasMember && hasGetter && hasSetter),
            "member descriptors should only be exposing either member or getter/setter");

        static constexpr char const *getName() { return name.data(); }
        static constexpr field_type owner_type::* getMember() { return member; }

        static constexpr auto getAccessor() {
            if constexpr (hasGetter) {
                return getter;
            } else {
                return member;
            }
        }

        template <typename O> requires std::same_as<std::remove_cvref_t<O>, owner_type>
        static constexpr auto get(O &&owner)-> decltype(std::invoke(getAccessor(), std::forward<O>(owner))) {
            return std::invoke(getAccessor(), std::forward<O>(owner));
        }

        template <typename O, typename V> requires std::derived_from<std::remove_cvref_t<O>, owner_type> && std::is_convertible_v<V, field_type const &>
        static constexpr void set(O &&owner, V &&value) {
            if constexpr (hasSetter) {
                (owner.*setter)(std::forward<V>(value));
            } else {
                owner.*member = std::forward<V>(value);
            }
        }
    };
}

#endif //CPPGAME_MEMBER_DESCRIPTOR_HPP
