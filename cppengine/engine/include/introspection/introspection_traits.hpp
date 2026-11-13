#ifndef INTROSPECTION_TRAITS_HPP
#define INTROSPECTION_TRAITS_HPP
#include <charconv>
#include <variant>

#include "platform/enum_key_code.hpp"

namespace cppengine {
    template <typename T>
    concept NonTriviallyIntrospectableType =
        TypeTraits<T>::defined_trait_v && TypeMemberTraits<T>::members_defined_v;

    template <typename T>
    concept TriviallyIntrospectableType =
        TypeTraits<T>::defined_trait_v && TypeTraits<T>::pod_type_v;

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
    concept StringArithmeticKeyConvertibleType = requires(std::string_view key, std::remove_cv_t<T> &value)
    {
        { std::from_chars(key.data(), key.data() + key.size(), value) } -> std::same_as<std::from_chars_result>;
    };

    template <typename T>
    concept StringKeyConvertibleType =
        std::same_as<std::remove_cv_t<T>, std::string>
    || std::same_as<std::remove_cv_t<T>, bool>
    || StringArithmeticKeyConvertibleType<T>;

    template <typename T>
    concept KeyStringConvertibleType = std::is_convertible_v<T const &, std::string_view>
    ||  requires(T const &value)
    {
        { std::to_string(value) } -> std::convertible_to<std::string>;
    };

    template <typename T>
    concept KeyValuePairType = requires {
        typename std::tuple_element<0, T>::type;
        typename std::tuple_element<1, T>::type;
    } && std::tuple_size_v<T> == 2
    && KeyStringConvertibleType<std::tuple_element_t<0, T>>;

    template <typename T> requires IterableSerialisableType<T>
    struct WritableElementType {
        using type = T::value_type;
    };

    template <typename T> requires AssociativeContainerType<T>
    struct WritableElementType<T> {
        using key_type = std::remove_cv_t<typename T::key_type>;
        using field_type = std::remove_cv_t<typename T::mapped_type>;

        using type = std::pair<key_type, field_type>;
    };

    template <typename T, std::size_t S> requires IterableSerialisableType<T[S]>
    struct WritableElementType<T[S]> {

        using type = std::remove_cv_t<T>;
    };

    template <typename T>
    concept BackInsertableType = IterableSerialisableType<T> && (requires (T &container, typename T::value_type value) {
        container.push_back(std::move(value));
    });

    template <typename T>
    concept InsertableType = IterableSerialisableType<T> && (requires(T &container, typename T::value_type value) {
        container.insert(std::move(value));
    });

    template <typename T>
    concept ResettableIterableType = IterableSerialisableType<T> && (requires(T &container) {
        container.clear();
    });

    template <typename T>
    concept DynamicIterableType = BackInsertableType<T> || InsertableType<T>;

    template <typename T>
    concept SerialisableType = std::is_convertible_v<T, std::string_view>
        || TriviallyIntrospectableType<T>
        || IterableSerialisableType<T>
        || NonTriviallyIntrospectableType<T>
        || KeyValuePairType<T>;

    template <typename T>
    concept DeserialisableType = !std::is_const_v<T> && (std::same_as<T, std::string> || TriviallyIntrospectableType<T>
        || IterableSerialisableType<T> || NonTriviallyIntrospectableType<T>
        || KeyValuePairType<T>);

    template <typename T>
        struct VariantTraits : std::false_type {
        using variants = ArgumentList<>;

        static constexpr bool serialisable = value;
    };

    template <typename ... Args>
    struct VariantTraits<std::variant<Args...>> : std::true_type {
        using variants = ArgumentList<Args...>;

        static constexpr bool serialisable = value && ((SerialisableType<Args> || DeserialisableType<Args>) &&...);

    };

    template <typename T>
    concept VariantSerialisableType = VariantTraits<std::remove_cvref_t<T>>::serialisable;
}

#endif