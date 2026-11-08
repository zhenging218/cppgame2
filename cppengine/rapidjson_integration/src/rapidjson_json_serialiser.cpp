//
// Created by Admin on 8/11/2026.
//

#include "rapidjson_integration.hpp"

namespace {
    template <typename T, typename OSW> requires (std::signed_integral<T> && !std::same_as<T, bool>)
    void write(rapidjson::Writer<OSW> &writer, T const &value) {
        if constexpr (sizeof(T) <= sizeof(int)) {
            writer.Int(value);
        } else {
            writer.Int64(value);
        }
    }

    template <typename T, typename OSW> requires (std::unsigned_integral<T> && !std::same_as<T, bool>)
    void write(rapidjson::Writer<OSW> &writer, T const &value) {
        if constexpr (sizeof(T) <= sizeof(unsigned int)) {
            writer.Uint(value);
        } else {
            writer.Uint64(value);
        }
    }

    template <typename T, typename OSW> requires std::floating_point<T>
    void write(rapidjson::Writer<OSW> &writer, T const &value) {
        writer.Double(value);
    }

    template <typename OSW>
    void write(rapidjson::Writer<OSW> &writer, std::string_view value) {
        writer.String(value.data(), value.size(), true);
    }

    template <typename OSW>
    void write(rapidjson::Writer<OSW> &writer, bool const &value) {
        writer.Bool(value);
    }

    template <typename T, typename OSW>
    void write(rapidjson::Writer<OSW> &writer, std::string_view key, T const &value) {
        writer.Key(key.data());
        write(writer, value);
    }
}

namespace cppengine {
    ObjectHandle<Serialiser> Serialiser::createJsonSerialiser(std::ostream &stream) {
        return createHandle<RapidJsonSerialiser>(stream);
    }

    void RapidJsonSerialiser::beginObject(std::string_view name) {
        writer.Key(name.data());
        writer.StartObject();
    }

    void RapidJsonSerialiser::beginObject() {
        writer.StartObject();
    }

    void RapidJsonSerialiser::endObject() {
        writer.EndObject();
    }

    void RapidJsonSerialiser::beginArray(std::string_view name) {
        writer.Key(name.data());
        writer.StartArray();
    }

    void RapidJsonSerialiser::beginArray() {
        writer.StartArray();
    }

    void RapidJsonSerialiser::endArray() {
        writer.EndArray();
    }

    void RapidJsonSerialiser::serialiseValue(const char &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const unsigned char &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const short &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const unsigned short &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const int &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const unsigned &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const long &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const unsigned long &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const long long &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const unsigned long long &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const float &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const double &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(const bool &value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view value) {
        write(writer, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const char &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const unsigned char &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const short &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const unsigned short &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const int &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const unsigned &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const long &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const unsigned long &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const long long &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const unsigned long long &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const float &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const double &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const bool &value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, std::string_view value) {
        write(writer, name, value);
    }

    void RapidJsonSerialiser::processSeparator() {
    }

    RapidJsonSerialiser::RapidJsonSerialiser(std::ostream &os) : wrapper(os), writer(wrapper) {
    }

    RapidJsonSerialiser::~RapidJsonSerialiser() = default;
}
