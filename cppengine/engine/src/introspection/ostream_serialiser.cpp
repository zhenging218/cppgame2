#include "engine.hpp"

namespace {
    template <typename T>
    void serialiseValueImpl(std::ostream &os, T const &value) {
        os << value;
    }

    template <>
    void serialiseValueImpl(std::ostream &os, std::string const &value) {
        os << "\"" << value << "\"";
    }

    template <typename T>
    void serialiseValueImpl(std::ostream &os, std::string_view name, T const &value) {
        os << name << ": ";
        serialiseValueImpl(os, value);
    }
}

namespace cppengine {
    OStreamSerialiser::OStreamSerialiser(std::ostream &os) : ostream(os) {

    }

    void OStreamSerialiser::beginArray(std::string_view name) {
        ostream << name << " : ";
        beginArray();
    }

    void OStreamSerialiser::beginArray() {
        ostream << "[ ";
    }

    void OStreamSerialiser::endArray() {
        ostream << " ]";
    }

    void OStreamSerialiser::beginObject(std::string_view name) {
        ostream << name << " : ";
        beginObject();
    }

    void OStreamSerialiser::beginObject() {
        ostream << "{ ";
    }

    void OStreamSerialiser::endObject() {
        ostream << " }";
    }

    void OStreamSerialiser::placeSeparator() {
        ostream << ", ";
    }

    void OStreamSerialiser::serialiseValue(std::string_view name, char const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, unsigned char const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, short const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, unsigned short const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, int const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, unsigned int const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, long const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, unsigned long const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, long long const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, unsigned long long const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, float const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, double const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, bool const &value) { serialiseValueImpl(ostream, name, value); }
    void OStreamSerialiser::serialiseValue(std::string_view name, std::string const &value) { serialiseValueImpl(ostream, name, value); }

    void OStreamSerialiser::serialiseValue(char const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(unsigned char const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(short const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(unsigned short const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(int const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(unsigned int const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(long const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(unsigned long const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(long long const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(unsigned long long const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(float const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(double const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(bool const &value) { serialiseValueImpl(ostream, value); }
    void OStreamSerialiser::serialiseValue(std::string const &value) { serialiseValueImpl(ostream, value); }
}
