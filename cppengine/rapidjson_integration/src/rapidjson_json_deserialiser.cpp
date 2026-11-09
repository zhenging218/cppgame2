//
// Created by Admin on 8/11/2026.
//

#include "rapidjson_integration.hpp"

namespace {
    rapidjson::Document parseStreamAsDocument(rapidjson::IStreamWrapper &wrapper) {
        rapidjson::Document d;
        d.ParseStream(wrapper);
        return d;
    }

    constexpr char const * jsonNodeTypes[] = {
        "null",
        "boolean (false)",
        "boolean (true)",
        "object",
        "array",
        "string",
        "number"
    };

    int rapidjsonTypeToJsonNodetype(rapidjson::Type type) {
        switch (type) {
            case rapidjson::kNullType:
                return 0;
            case rapidjson::kFalseType:
                return 1;
            case rapidjson::kTrueType:
                return 2;
            case rapidjson::kObjectType:
                return 3;
            case rapidjson::kArrayType:
                return 4;
            case rapidjson::kStringType:
                return 5;
            case rapidjson::kNumberType:
                return 6;
            default:
                throw std::runtime_error(std::format("unknown rapidjson type {}", static_cast<int>(type)));
        }
    }
}

namespace cppengine {
    struct RapidJsonDeserialiser::Frame {
        [[nodiscard]] virtual int getType() const = 0;
        virtual ~Frame() = 0;
    };

    struct RapidJsonDeserialiser::ObjectFrame : Frame {
        [[nodiscard]] int getType() const override;
        ~ObjectFrame() override;
    };

    struct RapidJsonDeserialiser::ArrayFrame : Frame {
        [[nodiscard]] int getType() const override;
        ~ArrayFrame() override;
    };

    template <typename T>
    struct RapidJsonDeserialiser::ValueFrame : Frame {
        [[nodiscard]] int getType() const override;



        ~ValueFrame() override;
    };

    int RapidJsonDeserialiser::ObjectFrame::getType() const {
        return rapidjsonTypeToJsonNodetype(rapidjson::kObjectType);
    }

    int RapidJsonDeserialiser::ArrayFrame::getType() const {
        return rapidjsonTypeToJsonNodetype(rapidjson::kArrayType);
    }

    template <typename T>
    int RapidJsonDeserialiser::ValueFrame<T>::getType() const {
        return rapidjsonTypeToJsonNodetype(rapidjson::kNullType);
    }

    RapidJsonDeserialiser::Frame::~Frame() = default;
    RapidJsonDeserialiser::ObjectFrame::~ObjectFrame() = default;
    RapidJsonDeserialiser::ArrayFrame::~ArrayFrame() = default;

    template <typename T>
    RapidJsonDeserialiser::ValueFrame<T>::~ValueFrame() = default;

    template <typename T> requires NonTriviallyIntrospectableType<T>
    ObjectHandle<RapidJsonDeserialiser::Frame> RapidJsonDeserialiser::createFrame(rapidjson::Value &node) {

    }

    template <typename T> requires TriviallyIntrospectableType<T>
    ObjectHandle<RapidJsonDeserialiser::Frame> RapidJsonDeserialiser::createFrame(rapidjson::Value &node) {

    }

    template <typename T> requires IterableSerialisableType<T>
    ObjectHandle<RapidJsonDeserialiser::Frame> RapidJsonDeserialiser::createFrame(rapidjson::Value &node) {

    }


    bool RapidJsonDeserialiser::convertBooleanValue(std::string_view value) {
    }

    void RapidJsonDeserialiser::processSeparator() {
    }

    std::string RapidJsonDeserialiser::getFieldKey() {
    }

    void RapidJsonDeserialiser::beginObject() {

    }

    void RapidJsonDeserialiser::beginObject(std::string_view name) {
    }

    void RapidJsonDeserialiser::beginObject(std::size_t at) {
    }

    void RapidJsonDeserialiser::endObject() {
    }

    std::size_t RapidJsonDeserialiser::beginArray() {
    }

    std::size_t RapidJsonDeserialiser::beginArray(std::string_view name) {
    }

    std::size_t RapidJsonDeserialiser::beginArray(std::size_t at) {
    }

    void RapidJsonDeserialiser::endArray() {
    }

    void RapidJsonDeserialiser::deserialiseValue(char &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(unsigned char &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(short &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(unsigned short &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(int &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(unsigned &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(unsigned long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(long long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(unsigned long long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(float &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(double &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(bool &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, char &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, unsigned char &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, short &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, unsigned short &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, int &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, unsigned &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, unsigned long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, long long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, unsigned long long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, float &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, double &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, bool &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::string_view name, std::string &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, char &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, unsigned char &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, short &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, unsigned short &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, int &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, unsigned &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, unsigned long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, long long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, unsigned long long &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, float &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, double &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, bool &value) {
    }

    void RapidJsonDeserialiser::deserialiseValue(std::size_t at, std::string &value) {
    }

    RapidJsonDeserialiser::RapidJsonDeserialiser(std::istream &is) : wrapper(is), document(parseStreamAsDocument(wrapper)) {
        // put the document into the stack as a frame
    }

    RapidJsonDeserialiser::~RapidJsonDeserialiser() = default;

}
