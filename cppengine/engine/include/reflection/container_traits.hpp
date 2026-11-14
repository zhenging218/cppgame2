//
// Created by Admin on 14/11/2026.
//

#ifndef CONTAINER_TRAITS_CPP
#define CONTAINER_TRAITS_CPP

#include <vector>
#include <list>
#include <stack>
#include <deque>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <forward_list>

#include "reflection_traits.hpp"
#include "string_literal.hpp"

#define DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(TYPE_NAME) \
    template<typename T> \
    struct TypeTraits<TYPE_NAME<T>> { \
        using type = TYPE_NAME<T>;\
        using super_type = type; \
        static constexpr std::size_t size = sizeof(type); \
        static constexpr StringLiteral name = concatLiterals(StringLiteral{#TYPE_NAME}, StringLiteral{"<"}, TypeTraits<T>::name, StringLiteral{">"}); \
        static constexpr char const *getName() { return name.data(); } \
        static constexpr bool defined_trait_v = true; \
        static constexpr bool pod_type_v = false; \
        static constexpr bool container_type_v = true; \
    }

#define DECL_DOUBLE_TEMPLATE_CONTAINER_TYPE(TYPE_NAME) \
    template<typename T, typename U> \
    struct TypeTraits<TYPE_NAME<T, U>> { \
        using type = TYPE_NAME<T, U>;\
        using super_type = type; \
        static constexpr std::size_t size = sizeof(type); \
        static constexpr StringLiteral name = concatLiterals(StringLiteral{#TYPE_NAME}, StringLiteral{"<"}, TypeTraits<T>::name, StringLiteral{","}, TypeTraits<U>::name, StringLiteral{">"}); \
        static constexpr char const *getName() { return name.data(); } \
        static constexpr bool defined_trait_v = true; \
        static constexpr bool pod_type_v = false; \
        static constexpr bool container_type_v = true; \
    }

namespace cppengine {
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::vector);
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::list);
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::forward_list);
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::stack);
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::deque);
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::queue);
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::priority_queue);
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::set);
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::multiset);
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::unordered_set);
    DECL_SINGLE_TEMPLATE_CONTAINER_TYPE(std::unordered_multiset);

    DECL_DOUBLE_TEMPLATE_CONTAINER_TYPE(std::map);
    DECL_DOUBLE_TEMPLATE_CONTAINER_TYPE(std::multimap);
    DECL_DOUBLE_TEMPLATE_CONTAINER_TYPE(std::unordered_map);
    DECL_DOUBLE_TEMPLATE_CONTAINER_TYPE(std::unordered_multimap);
}

#undef DECL_SINGLE_TEMPLATE_CONTAINER_TYPE
#undef DECL_DOUBLE_TEMPLATE_CONTAINER_TYPE

#endif //CONTAINER_TRAITS_CPP
