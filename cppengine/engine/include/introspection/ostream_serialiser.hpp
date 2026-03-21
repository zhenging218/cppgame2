#ifndef OSTREAM_SERIALISER_HPP
#define OSTREAM_SERIALISER_HPP

#include "serialiser.hpp"

namespace cppengine {
    class OStreamSerialiser : public Serialiser {
    private:
        std::ostream &ostream;
    protected:
         void beginObject(std::string_view name) override;
         void beginArray(std::string_view name) override;

         void serialiseValue(std::string_view name, char const &value) override;
         void serialiseValue(std::string_view name, unsigned char const &value) override;
         void serialiseValue(std::string_view name, short const &value) override;
         void serialiseValue(std::string_view name, unsigned short const &value) override;
         void serialiseValue(std::string_view name, int const &value) override;
         void serialiseValue(std::string_view name, unsigned int const &value) override;
         void serialiseValue(std::string_view name, long const &value) override;
         void serialiseValue(std::string_view name, unsigned long const &value) override;
         void serialiseValue(std::string_view name, long long const &value) override;
         void serialiseValue(std::string_view name, unsigned long long const &value) override;
         void serialiseValue(std::string_view name, float const &value) override;
         void serialiseValue(std::string_view name, double const &value) override;
         void serialiseValue(std::string_view name, bool const &value) override;
         void serialiseValue(std::string_view name, std::string const &value) override;

        void beginObject() override;
        void beginArray() override;

        void serialiseValue(const char &value) override;
        void serialiseValue(const unsigned char &value) override;
        void serialiseValue(const short &value) override;
        void serialiseValue(const unsigned short &value) override;
        void serialiseValue(const int &value) override;
        void serialiseValue(const unsigned &value) override;
        void serialiseValue(const long &value) override;
        void serialiseValue(const unsigned long &value) override;
        void serialiseValue(const long long &value) override;
        void serialiseValue(const unsigned long long &value) override;
        void serialiseValue(const float &value) override;
        void serialiseValue(const double &value) override;
        void serialiseValue(const bool &value) override;
        void serialiseValue(const std::string &value) override;

        void placeSeparator() override;

         void endObject() override;
         void endArray() override;

    public:
        OStreamSerialiser(std::ostream &os);
        OStreamSerialiser(OStreamSerialiser const &) = delete;
        OStreamSerialiser(OStreamSerialiser &&) noexcept = delete;
        OStreamSerialiser &operator=(OStreamSerialiser const &) = delete;
        OStreamSerialiser &operator=(OStreamSerialiser &&) noexcept = delete;

        ~OStreamSerialiser() override;
    };

    inline OStreamSerialiser::~OStreamSerialiser() = default;
}

template <typename T> requires (cppengine::NonTriviallyIntrospectableType<T> || cppengine::IterableSerialisableType<T>)
std::ostream &operator<<(std::ostream &os, T const &value) {
    cppengine::OStreamSerialiser serialiser{os};
    serialiser.serialise(value);
    return os;
}

#endif