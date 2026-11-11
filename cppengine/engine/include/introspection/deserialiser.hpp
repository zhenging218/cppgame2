#ifndef DESERIALISER_HPP
#define DESERIALISER_HPP

#include "reflection/type_descriptor.hpp"
#include "introspection_traits.hpp"

namespace cppengine {
    class Deserialiser {
    private:

        template <typename T> requires StringKeyConvertibleType<T>
        T convertFieldKey(std::string_view key);

        template <typename Visitor, typename ... T>
        void deserialiseObjectFields(ArgumentList<T...>, Visitor &&v);

        template <typename T> requires KeyValuePairType<T>
        void deserialiseKeyValuePair(std::string_view name, T &value);

        template <typename T> requires KeyValuePairType<T>
        void deserialiseKeyValuePair(std::size_t at, T &value);

        template <typename T> requires KeyValuePairType<T>
        void deserialiseKeyValuePair(T &value);

        template <typename T, typename S> requires IterableSerialisableType<T>
        void deserialiseArrayElements(T &array, S size);

        template <typename T> requires IterableSerialisableType<T>
        void deserialiseArray(std::string_view name, T &array);

        template <typename T> requires IterableSerialisableType<T>
        void deserialiseArray(std::size_t at, T &array);

        template <typename T> requires IterableSerialisableType<T>
        void deserialiseArray(T &array);

        template <typename T>
        void deserialiseObject(std::string_view name, T &object);

        template <typename T>
        void deserialiseObject(std::size_t at, T &object);

        template <typename T>
        void deserialiseObject(T &object);

        template <typename T> requires DeserialisableType<T>
        void deserialiseValue(std::string_view name, T &value);

        template <typename T> requires DeserialisableType<T>
        void deserialiseValue(std::size_t at, T &value);

        template <typename T> requires DeserialisableType<T>
        void deserialiseValue(T &value);

    protected:
        virtual bool convertBooleanValue(std::string_view value) = 0;

        virtual void processSeparator() = 0;

        virtual std::string getFieldKey() = 0;

        virtual void beginObject() = 0;
        virtual void beginObject(std::string_view name) = 0;
        virtual void beginObject(std::size_t at) = 0;
        virtual void endObject() = 0;

        virtual std::size_t beginArray() = 0;
        virtual std::size_t beginArray(std::string_view name) = 0;
        virtual std::size_t beginArray(std::size_t at) = 0;
        virtual void endArray() = 0;

        virtual void deserialiseValue(char &value) = 0;
        virtual void deserialiseValue(unsigned char &value) = 0;
        virtual void deserialiseValue(short &value) = 0;
        virtual void deserialiseValue(unsigned short &value) = 0;
        virtual void deserialiseValue(int &value) = 0;
        virtual void deserialiseValue(unsigned int &value) = 0;
        virtual void deserialiseValue(long &value) = 0;
        virtual void deserialiseValue(unsigned long &value) = 0;
        virtual void deserialiseValue(long long &value) = 0;
        virtual void deserialiseValue(unsigned long long &value) = 0;
        virtual void deserialiseValue(float &value) = 0;
        virtual void deserialiseValue(double &value) = 0;
        virtual void deserialiseValue(bool &value) = 0;
        virtual void deserialiseValue(std::string &value) = 0;

        virtual void deserialiseValue(std::string_view name, char &value) = 0;
        virtual void deserialiseValue(std::string_view name, unsigned char &value) = 0;
        virtual void deserialiseValue(std::string_view name, short &value) = 0;
        virtual void deserialiseValue(std::string_view name, unsigned short &value) = 0;
        virtual void deserialiseValue(std::string_view name, int &value) = 0;
        virtual void deserialiseValue(std::string_view name, unsigned int &value) = 0;
        virtual void deserialiseValue(std::string_view name, long &value) = 0;
        virtual void deserialiseValue(std::string_view name, unsigned long &value) = 0;
        virtual void deserialiseValue(std::string_view name, long long &value) = 0;
        virtual void deserialiseValue(std::string_view name, unsigned long long &value) = 0;
        virtual void deserialiseValue(std::string_view name, float &value) = 0;
        virtual void deserialiseValue(std::string_view name, double &value) = 0;
        virtual void deserialiseValue(std::string_view name, bool &value) = 0;
        virtual void deserialiseValue(std::string_view name, std::string &value) = 0;

        virtual void deserialiseValue(std::size_t at, char &value) = 0;
        virtual void deserialiseValue(std::size_t at, unsigned char &value) = 0;
        virtual void deserialiseValue(std::size_t at, short &value) = 0;
        virtual void deserialiseValue(std::size_t at, unsigned short &value) = 0;
        virtual void deserialiseValue(std::size_t at, int &value) = 0;
        virtual void deserialiseValue(std::size_t at, unsigned int &value) = 0;
        virtual void deserialiseValue(std::size_t at, long &value) = 0;
        virtual void deserialiseValue(std::size_t at, unsigned long &value) = 0;
        virtual void deserialiseValue(std::size_t at, long long &value) = 0;
        virtual void deserialiseValue(std::size_t at, unsigned long long &value) = 0;
        virtual void deserialiseValue(std::size_t at, float &value) = 0;
        virtual void deserialiseValue(std::size_t at, double &value) = 0;
        virtual void deserialiseValue(std::size_t at, bool &value) = 0;
        virtual void deserialiseValue(std::size_t at, std::string &value) = 0;

    public:

        template <typename T>
        void deserialise(T &dest);

        virtual ~Deserialiser() = 0;

        static ObjectHandle<Deserialiser> createJsonDeserialiser(std::istream &stream);
    };

    inline Deserialiser::~Deserialiser() = default;
}

#endif