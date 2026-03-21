#ifndef SERIALISER_HPP
#define SERIALISER_HPP

#include <string>

#include "reflection/type_descriptor.hpp"

namespace cppengine {
    template <typename T>
    concept NonTriviallySerialisableType = TypeTraits<T>::defined_trait_v;

    template <typename T>
    concept IterableSerialisableType =
    !std::is_convertible_v<T, std::string_view> &&
    (requires (T const &t) {
        { std::begin(t) } -> std::forward_iterator;
        { std::end(t) } -> std::forward_iterator;
    } || std::is_array_v<T>);

    class Serialiser {
    private:

        template <typename T>
        void serialiseValue(T const &value);

        template <typename T>
        void serialiseValue(std::string_view name, T const &value);

        template <typename T>
        void serialiseObject(std::string_view name, T const &object);

        template <typename T>
        void serialiseObject(T const &object);

        template <typename Visitor, typename ... T>
        void serialiseObjectFields(ArgumentList<T...>, Visitor &&v);

        template <typename T> requires IterableSerialisableType<T>
        void serialiseArray(std::string_view name, T const &array);

        template <typename T> requires IterableSerialisableType<T>
        void serialiseArray(T const &array);

    protected:
        virtual void beginObject(std::string_view name) = 0;
        virtual void beginObject() = 0;
        virtual void beginArray(std::string_view name) = 0;
        virtual void beginArray() = 0;

        virtual void serialiseValue(char const &value) = 0;
        virtual void serialiseValue(unsigned char const &value) = 0;
        virtual void serialiseValue(short const &value) = 0;
        virtual void serialiseValue(unsigned short const &value) = 0;
        virtual void serialiseValue(int const &value) = 0;
        virtual void serialiseValue(unsigned int const &value) = 0;
        virtual void serialiseValue(long const &value) = 0;
        virtual void serialiseValue(unsigned long const &value) = 0;
        virtual void serialiseValue(long long const &value) = 0;
        virtual void serialiseValue(unsigned long long const &value) = 0;
        virtual void serialiseValue(float const &value) = 0;
        virtual void serialiseValue(double const &value) = 0;
        virtual void serialiseValue(bool const &value) = 0;
        virtual void serialiseValue(std::string const &value) = 0;

        virtual void serialiseValue(std::string_view name, char const &value) = 0;
        virtual void serialiseValue(std::string_view name, unsigned char const &value) = 0;
        virtual void serialiseValue(std::string_view name, short const &value) = 0;
        virtual void serialiseValue(std::string_view name, unsigned short const &value) = 0;
        virtual void serialiseValue(std::string_view name, int const &value) = 0;
        virtual void serialiseValue(std::string_view name, unsigned int const &value) = 0;
        virtual void serialiseValue(std::string_view name, long const &value) = 0;
        virtual void serialiseValue(std::string_view name, unsigned long const &value) = 0;
        virtual void serialiseValue(std::string_view name, long long const &value) = 0;
        virtual void serialiseValue(std::string_view name, unsigned long long const &value) = 0;
        virtual void serialiseValue(std::string_view name, float const &value) = 0;
        virtual void serialiseValue(std::string_view name, double const &value) = 0;
        virtual void serialiseValue(std::string_view name, bool const &value) = 0;
        virtual void serialiseValue(std::string_view name, std::string const &value) = 0;

        virtual void placeSeparator() = 0;

        virtual void endObject() = 0;
        virtual void endArray() = 0;

    public:

        template <typename T>
        void serialise(T const &src);

        virtual ~Serialiser() = 0;
    };

    inline Serialiser::~Serialiser() = default;
}

#endif