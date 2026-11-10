//
// Created by Admin on 8/11/2026.
//

#include <utility>

#include "rapidjson_integration.hpp"

namespace {
    cppengine::ObjectHandle<const rapidjson::Document> parseStreamAsDocument(rapidjson::IStreamWrapper &wrapper) {
        cppengine::ObjectHandle<rapidjson::Document> d = cppengine::createHandle<rapidjson::Document>();
        d->ParseStream(wrapper);
        return const_handle_cast<const rapidjson::Document>(d);
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

    int rapidjsonTypeToJsonNodeType(rapidjson::Type type) {
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

    template <typename T> requires (std::signed_integral<T> && !std::same_as<T, bool>)
    T read(rapidjson::Value const &value) {
        if constexpr (sizeof(T) <= sizeof(int)) {
            return value.GetInt();
        } else {
            return value.GetInt64();
        }
    }

    template <typename T, typename F> requires (std::unsigned_integral<T> && !std::same_as<T, bool>)
    T read(rapidjson::Value const &value) {
        if constexpr (sizeof(T) <= sizeof(unsigned int)) {
            return value.GetUint();
        } else {
            return value.GetUint64();
        }
    }

    template <typename T> requires std::is_floating_point_v<T>
    T read(rapidjson::Value const &value) {
        return value.GetFloat();
    }

    template<typename T> requires std::same_as<T, bool>
    T read(rapidjson::Value const &value) {
        return value.GetBool();
    }

    template <typename T> requires std::same_as<T, std::string>
    T read(rapidjson::Value const &value) {
        return std::string(value.GetString());
    }

}

namespace cppengine {
    struct RapidJsonDeserialiser::Frame {
        [[nodiscard]] virtual int getType() const = 0;
        [[nodiscard]] virtual std::string_view getName() const = 0;
        [[nodiscard]] virtual bool isRoot() const;
        virtual ~Frame() = 0;
    };

    struct RapidJsonDeserialiser::ObjectFrame : Frame {
        using value_type = std::remove_cvref_t<decltype(std::declval<rapidjson::Value const &>().GetObject())>;

        std::string name;
        std::reference_wrapper<const value_type> object;

        ObjectFrame(const value_type &object_);
        ObjectFrame(std::string_view name_, const value_type &object_);

        [[nodiscard]] int getType() const override;
        [[nodiscard]] std::string_view getName() const override;

        template <typename T> requires TriviallyIntrospectableType<T> || std::same_as<T, std::string>
        [[nodiscard]] T getValue(std::string_view fieldName) const;

        [[nodiscard]] ObjectHandle<ObjectFrame> getObject(std::string_view fieldName) const;

        [[nodiscard]] ObjectHandle<ArrayFrame> getArray(std::string_view fieldName) const;

        ~ObjectFrame() override;
    };

    struct RapidJsonDeserialiser::ArrayFrame : Frame {
        using value_type = std::remove_cvref_t<decltype(std::declval<rapidjson::Value const &>().GetArray())>;

        std::string name;
        std::reference_wrapper<const value_type> array;

        ArrayFrame(value_type const &array_);

        [[nodiscard]] int getType() const override;
        [[nodiscard]] std::string_view getName() const override;
        [[nodiscard]] std::size_t getSize() const;

        template <typename U> requires TriviallyIntrospectableType<U> || std::same_as<U, std::string>
        [[nodiscard]] U getValue(std::size_t at) const;

        [[nodiscard]] ObjectHandle<ObjectFrame> getObject(std::size_t at) const;

        [[nodiscard]] ObjectHandle<ArrayFrame> getArray(std::size_t at) const;

        ~ArrayFrame() override;
    };

    struct RapidJsonDeserialiser::RootFrame : Frame {
        ObjectHandle<const rapidjson::Document> document;

        RootFrame(ObjectHandle<const rapidjson::Document> document_);

        [[nodiscard]] int getType() const override;
        [[nodiscard]] std::string_view getName() const override;
        [[nodiscard]] bool isRoot() const override;

        template <typename U> requires TriviallyIntrospectableType<U> || std::same_as<U, std::string>
        [[nodiscard]] U getValue() const;
        [[nodiscard]] ObjectHandle<ObjectFrame> getObject() const;
        [[nodiscard]] ObjectHandle<ArrayFrame> getArray() const;

        ~RootFrame() override;
    };

    bool RapidJsonDeserialiser::Frame::isRoot() const {
        return false;
    }

    RapidJsonDeserialiser::ObjectFrame::ObjectFrame(const value_type &object_) : ObjectFrame("", object_) {
    }

    RapidJsonDeserialiser::ObjectFrame::ObjectFrame(std::string_view name_, const value_type &object_) : name(name_), object(object_) {

    }

    int RapidJsonDeserialiser::ObjectFrame::getType() const {
        return rapidjsonTypeToJsonNodeType(rapidjson::kObjectType);
    }

    std::string_view RapidJsonDeserialiser::ObjectFrame::getName() const {
        return "";
    }

    ObjectHandle<RapidJsonDeserialiser::ObjectFrame> RapidJsonDeserialiser::ObjectFrame::getObject(
        std::string_view fieldName) const {
        const auto &it = object.get().FindMember(fieldName.data());

        if (it != object.get().MemberEnd()) {
            return createHandle<ObjectFrame>(it->name.GetString(), it->value.GetObject());
        }

        throw std::runtime_error(std::format("object has no such member {} of type {}", fieldName, jsonNodeTypes[getType()]));
    }

    ObjectHandle<RapidJsonDeserialiser::ArrayFrame> RapidJsonDeserialiser::ObjectFrame::getArray(
        std::string_view fieldName) const {

        const auto &it = object.get().FindMember(fieldName.data());

        if (it != object.get().MemberEnd()) {
            return createHandle<ArrayFrame>(it->value.GetArray());
        }

        throw std::runtime_error(std::format("object has no such member {} of type {}", fieldName, jsonNodeTypes[getType()]));
    }

    template <typename T> requires TriviallyIntrospectableType<T> || std::same_as<T, std::string>
    T RapidJsonDeserialiser::ObjectFrame::getValue(std::string_view fieldName) const {
        const auto &it = object.get().FindMember(fieldName.data());

        if (it != object.get().MemberEnd()) {
            return read<T>(it->value);
        }

        throw std::runtime_error(std::format("object has no such member {} of type {}", fieldName, TypeDescriptor::getTypeDescriptor<T>()->getName()));
    }

    RapidJsonDeserialiser::ArrayFrame::ArrayFrame(value_type const &array_) : array(array_) {
    }

    int RapidJsonDeserialiser::ArrayFrame::getType() const {
        return rapidjsonTypeToJsonNodeType(rapidjson::kArrayType);
    }

    std::string_view RapidJsonDeserialiser::ArrayFrame::getName() const {
        return "";
    }

    std::size_t RapidJsonDeserialiser::ArrayFrame::getSize() const {
        return array.get().Size();
    }

    ObjectHandle<RapidJsonDeserialiser::ObjectFrame> RapidJsonDeserialiser::ArrayFrame::getObject(
        std::size_t at) const {
        return createHandle<ObjectFrame>(array.get()[at].GetObject());
    }

    ObjectHandle<RapidJsonDeserialiser::ArrayFrame> RapidJsonDeserialiser::ArrayFrame::getArray(
        std::size_t at) const {
        return createHandle<ArrayFrame>(array.get()[at].GetArray());
    }

    template<typename T> requires TriviallyIntrospectableType<T> || std::same_as<T, std::string>
    T RapidJsonDeserialiser::ArrayFrame::getValue(std::size_t at) const {
        return read<T>(array.get()[at]);
    }

    RapidJsonDeserialiser::Frame::~Frame() = default;

    RapidJsonDeserialiser::ObjectFrame::~ObjectFrame() = default;

    RapidJsonDeserialiser::ArrayFrame::~ArrayFrame() = default;

    RapidJsonDeserialiser::RootFrame::RootFrame(ObjectHandle<const rapidjson::Document> document_) : document(std::move(document_)) {
    }

    int RapidJsonDeserialiser::RootFrame::getType() const {
        return rapidjsonTypeToJsonNodeType(document->GetType());
    }

    std::string_view RapidJsonDeserialiser::RootFrame::getName() const {
        return "";
    }

    bool RapidJsonDeserialiser::RootFrame::isRoot() const {
        return true;
    }

    ObjectHandle<RapidJsonDeserialiser::ObjectFrame> RapidJsonDeserialiser::RootFrame::getObject() const {
        if (getType() == rapidjsonTypeToJsonNodeType(rapidjson::kObjectType)) {
            return createHandle<ObjectFrame>(document->GetObject());
        }
        return nullptr;
    }

    ObjectHandle<RapidJsonDeserialiser::ArrayFrame> RapidJsonDeserialiser::RootFrame::getArray() const {
        if (getType() == rapidjsonTypeToJsonNodeType(rapidjson::kArrayType)) {
            return createHandle<ArrayFrame>(document->GetArray());
        }
        return nullptr;
    }

    template<typename U> requires TriviallyIntrospectableType<U> || std::same_as<U, std::string>
    U RapidJsonDeserialiser::RootFrame::getValue() const {
        return read<U>(document);
    }

    RapidJsonDeserialiser::RootFrame::~RootFrame() = default;

    bool RapidJsonDeserialiser::convertBooleanValue(std::string_view value) {
        return value == "true";
    }

    void RapidJsonDeserialiser::processSeparator() {
    }

    std::string RapidJsonDeserialiser::getFieldKey() {

    }

    void RapidJsonDeserialiser::beginObject() {
        // should only ever be called on the root
    }

    void RapidJsonDeserialiser::beginObject(std::string_view name) {
    }

    void RapidJsonDeserialiser::beginObject(std::size_t at) {
    }

    void RapidJsonDeserialiser::endObject() {
        frames.pop();
    }

    std::size_t RapidJsonDeserialiser::beginArray() {
        // should only ever be called on the root
    }

    std::size_t RapidJsonDeserialiser::beginArray(std::string_view name) {
    }

    std::size_t RapidJsonDeserialiser::beginArray(std::size_t at) {
    }

    void RapidJsonDeserialiser::endArray() {
        frames.pop();
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

    RapidJsonDeserialiser::RapidJsonDeserialiser(std::istream &is) : wrapper(is),
        frames(std::deque<ObjectHandle<Frame>>{createHandle<RootFrame>(parseStreamAsDocument(wrapper))}) {
    }

    RapidJsonDeserialiser::~RapidJsonDeserialiser() = default;

}
