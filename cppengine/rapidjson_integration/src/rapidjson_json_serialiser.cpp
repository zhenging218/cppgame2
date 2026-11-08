//
// Created by Admin on 8/11/2026.
//

#include "rapidjson_integration.hpp"

namespace cppengine {
    ObjectHandle<Serialiser> Serialiser::createJsonSerialiser(std::ostream &stream) {
        return createHandle<RapidJsonSerialiser>();
    }

    void RapidJsonSerialiser::beginObject(std::string_view name) {
    }

    void RapidJsonSerialiser::beginObject() {
    }

    void RapidJsonSerialiser::endObject() {
    }

    void RapidJsonSerialiser::beginArray(std::string_view name) {
    }

    void RapidJsonSerialiser::beginArray() {
    }

    void RapidJsonSerialiser::endArray() {
    }

    void RapidJsonSerialiser::serialiseValue(const char &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const unsigned char &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const short &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const unsigned short &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const int &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const unsigned &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const long &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const unsigned long &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const long long &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const unsigned long long &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const float &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const double &value) {
    }

    void RapidJsonSerialiser::serialiseValue(const bool &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const char &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const unsigned char &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const short &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const unsigned short &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const int &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const unsigned &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const long &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const unsigned long &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const long long &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const unsigned long long &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const float &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const double &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, const bool &value) {
    }

    void RapidJsonSerialiser::serialiseValue(std::string_view name, std::string_view value) {
    }

    void RapidJsonSerialiser::processSeparator() {
    }

    RapidJsonSerialiser::~RapidJsonSerialiser() = default;
}
