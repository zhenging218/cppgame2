#ifndef SERIALISER_HPP
#define SERIALISER_HPP

#include <string>

#include "reflection/type_descriptor.hpp"
#include "introspection_traits.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {


    class Serialiser {
    private:
        template <typename T> requires KeyStringConvertibleType<T>
        std::string convertKey(T const &key);

        template <typename T> requires VariantSerialisableType<T>
        void serialiseVariant(std::string_view name, T const &value);

        template <typename T> requires VariantSerialisableType<T>
        void serialiseVariant(T const &value);

        template <typename T> requires (KeyValuePairType<T>)
        void serialiseKeyValuePair(std::string_view name, T const &value);

        template <typename T> requires (KeyValuePairType<T>)
        void serialiseKeyValuePair(T const &value);

        template <typename T> requires SerialisableType<T>
        void serialiseValue(T const &value);

        template <typename T> requires SerialisableType<T>
        void serialiseValue(std::string_view name, T const &value);

        template <typename T>
        void serialiseObject(std::string_view name, T const &object);

        template <typename T>
        void serialiseObject(T const &object);

        template <typename Visitor, typename ... T>
        void serialiseObjectFields(ArgumentList<T...>, Visitor &&v);

        template <typename T>
        void serialiseArrayElements(T const &array);

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
        virtual void serialiseValue(std::string_view value) = 0;

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
        virtual void serialiseValue(std::string_view name, std::string_view value) = 0;

        virtual void processSeparator() = 0;

        virtual void endObject() = 0;
        virtual void endArray() = 0;

    public:

        template <typename T>
        void serialise(T const &src);

        virtual ~Serialiser() = 0;

        static ObjectHandle<Serialiser> createJsonSerialiser(std::ostream &stream);
    };

    inline Serialiser::~Serialiser() = default;
}

#endif