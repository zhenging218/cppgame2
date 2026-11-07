#ifndef INTROSPECTION_TRAITS_HPP
#define INTROSPECTION_TRAITS_HPP

namespace cppengine {
    template <typename T>
    concept NonTriviallyIntrospectableType =
        TypeTraits<T>::defined_trait_v && TypeMemberTraits<T>::members_defined_v;

    template <typename T>
    concept IterableSerialisableType =
    !std::is_convertible_v<T, std::string_view> &&
    (requires (T const &t) {
        { std::begin(t) } -> std::forward_iterator;
        { std::end(t) } -> std::forward_iterator;
    } || std::is_array_v<T>);

    template <typename T>
    concept AssociativeContainerType = requires {
        typename T::key_type;
        typename T::mapped_type;
    } && IterableSerialisableType<T>;

    template <typename T>
    concept KeyValuePairType = requires {
        typename std::tuple_element<0, T>::type;
        typename std::tuple_element<1, T>::type;
    } && std::tuple_size_v<T> == 2
    && std::is_same_v<std::remove_cv_t<std::tuple_element_t<0, T>>, std::string>;

    template <typename T>
    concept BackInsertableType = IterableSerialisableType<T> && (requires (T &container, typename T::value_type value) {
        container.push_back(std::move(value));
    });

    template <typename T>
    concept InsertableType = IterableSerialisableType<T> && (requires(T &container, typename T::value_type value) {
        container.insert(std::move(value));
    });

    template <typename T>
    concept DynamicIterableType = BackInsertableType<T> || InsertableType<T>;

}

#endif