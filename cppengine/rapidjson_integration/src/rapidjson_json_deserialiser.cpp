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
        virtual ~Frame() = 0;
    };

    template <typename T> requires NonTriviallyIntrospectableType<T>
    struct RapidJsonDeserialiser::ObjectFrame : Frame {
        using value_type = std::remove_cvref_t<decltype(std::declval<rapidjson::Value const &>().GetObject())>;

        std::string name;
        std::reference_wrapper<const value_type> object;

        ObjectFrame(const value_type &object_);

        [[nodiscard]] int getType() const override;
        [[nodiscard]] std::string_view getName() const override;

        template <typename U> requires TriviallyIntrospectableType<U>
        [[nodiscard]] U getValue(std::string_view name) const;

        template <typename U> requires NonTriviallyIntrospectableType<U>
        [[nodiscard]] ObjectHandle<ObjectFrame<U>> getObject(std::string_view name) const;

        template <typename U> requires IterableSerialisableType<U>
        [[nodiscard]] ObjectHandle<ArrayFrame<U>> getArray(std::string_view name) const;

        ~ObjectFrame() override;
    };

    template <typename T> requires IterableSerialisableType<T>
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

        template <typename U> requires NonTriviallyIntrospectableType<T>
        [[nodiscard]] ObjectHandle<ObjectFrame<U>> getObject(std::size_t at) const;

        template <typename U> requires IterableSerialisableType<T>
        [[nodiscard]] ObjectHandle<ArrayFrame<U>> getArray(std::size_t at) const;

        ~ArrayFrame() override;
    };

    template <typename T> requires TriviallyIntrospectableType<T>
    struct RapidJsonDeserialiser::ValueFrame : Frame {

        std::string name;
        std::reference_wrapper<const rapidjson::Value> value;

        ValueFrame(rapidjson::Value const &value_);

        [[nodiscard]] int getType() const override;
        [[nodiscard]] std::string_view getName() const override;

        [[nodiscard]] T getValue() const;

        ~ValueFrame() override;
    };

    template<typename T> requires NonTriviallyIntrospectableType<T>
    RapidJsonDeserialiser::ObjectFrame<T>::ObjectFrame(const value_type &object_) : object(object_) {

    }

    template <typename T> requires NonTriviallyIntrospectableType<T>
    int RapidJsonDeserialiser::ObjectFrame<T>::getType() const {
        return rapidjsonTypeToJsonNodetype(rapidjson::kObjectType);
    }

    template<typename T> requires NonTriviallyIntrospectableType<T>
    std::string_view RapidJsonDeserialiser::ObjectFrame<T>::getName() const {
        return object.get().
    }

    template<typename T> requires NonTriviallyIntrospectableType<T>
    template <typename U> requires TriviallyIntrospectableType<U>
    U RapidJsonDeserialiser::ObjectFrame<T>::getValue(std::string_view name) const {
        const auto &it = object.get().FindMember(name.data());

        if (it != object.get().MemberEnd()) {
            return read<U>(it->value);
        }

        throw std::runtime_error(std::format("object has no such member {} of type {}", name, TypeDescriptor::getTypeDescriptor<U>()->getName()));
    }

    template<typename T> requires NonTriviallyIntrospectableType<T>
    template<typename U> requires NonTriviallyIntrospectableType<U>
    ObjectHandle<RapidJsonDeserialiser::ObjectFrame<U>> RapidJsonDeserialiser::ObjectFrame<T>::getObject(
        std::string_view name) const {
        const auto &it = object.get().FindMember(name.data());

        if (it != object.get().MemberEnd()) {
            return createHandle<ObjectFrame<U>>(it->value.GetObject());
        }

        throw std::runtime_error(std::format("object has no such member {} of type {}", name, TypeDescriptor::getTypeDescriptor<U>()->getName()));
    }

    template<typename T> requires NonTriviallyIntrospectableType<T>
    template<typename U> requires IterableSerialisableType<U>
    ObjectHandle<RapidJsonDeserialiser::ArrayFrame<U>> RapidJsonDeserialiser::ObjectFrame<T>::getArray(
        std::string_view name) const {

        const auto &it = object.get().FindMember(name.data());

        if (it != object.get().MemberEnd()) {
            return createHandle<ArrayFrame<U>>(it->value.GetArray());
        }

        throw std::runtime_error(std::format("object has no such member {} of type {}", name, TypeDescriptor::getTypeDescriptor<U>()->getName()));
    }

    template<typename T> requires IterableSerialisableType<T>
    RapidJsonDeserialiser::ArrayFrame<T>::ArrayFrame(value_type const &array_) : array(array_) {
    }

    template <typename T> requires IterableSerialisableType<T>
    int RapidJsonDeserialiser::ArrayFrame<T>::getType() const {
        return rapidjsonTypeToJsonNodetype(rapidjson::kArrayType);
    }

    template<typename T> requires IterableSerialisableType<T>
    std::string_view RapidJsonDeserialiser::ArrayFrame<T>::getName() const {
    }

    template<typename T> requires IterableSerialisableType<T>
    std::size_t RapidJsonDeserialiser::ArrayFrame<T>::getSize() const {
        return array.get().Size();
    }

    template<typename T> requires IterableSerialisableType<T>
    template<typename U> requires TriviallyIntrospectableType<U> || std::same_as<U, std::string>
    U RapidJsonDeserialiser::ArrayFrame<T>::getValue(std::size_t at) const {
        return read<U>(array.get()[at]);
    }

    template<typename T> requires IterableSerialisableType<T>
    template<typename U> requires NonTriviallyIntrospectableType<T>
    ObjectHandle<RapidJsonDeserialiser::ObjectFrame<U>> RapidJsonDeserialiser::ArrayFrame<T>::getObject(
        std::size_t at) const {
        return createHandle<ObjectFrame<U>>(array.get()[at].GetObject());
    }

    template<typename T> requires IterableSerialisableType<T>
    template<typename U> requires IterableSerialisableType<T>
    ObjectHandle<RapidJsonDeserialiser::ArrayFrame<U>> RapidJsonDeserialiser::ArrayFrame<T>::getArray(
        std::size_t at) const {
        return createHandle<ArrayFrame<U>>(array.get()[at].GetArray());
    }

    template<typename T> requires TriviallyIntrospectableType<T>
    RapidJsonDeserialiser::ValueFrame<T>::ValueFrame(rapidjson::Value const &value_) : value(value_) {
    }

    template <typename T> requires TriviallyIntrospectableType<T>
    int RapidJsonDeserialiser::ValueFrame<T>::getType() const {
        return rapidjsonTypeToJsonNodetype(value.get().GetType());
    }

    template<typename T> requires TriviallyIntrospectableType<T>
    std::string_view RapidJsonDeserialiser::ValueFrame<T>::getName() const {
    }

    template <typename T> requires TriviallyIntrospectableType<T>
    T RapidJsonDeserialiser::ValueFrame<T>::getValue() const {
        return read<T>(value.get());
    }

    RapidJsonDeserialiser::Frame::~Frame() = default;

    template <typename T> requires NonTriviallyIntrospectableType<T>
    RapidJsonDeserialiser::ObjectFrame<T>::~ObjectFrame() = default;

    template <typename T> requires IterableSerialisableType<T>
    RapidJsonDeserialiser::ArrayFrame<T>::~ArrayFrame() = default;

    template <typename T> requires TriviallyIntrospectableType<T>
    RapidJsonDeserialiser::ValueFrame<T>::~ValueFrame() = default;

    template <typename T> requires NonTriviallyIntrospectableType<T>
    ObjectHandle<RapidJsonDeserialiser::Frame> RapidJsonDeserialiser::createFrame(rapidjson::Value const &node) {
        return createHandle<ObjectFrame<T>>(node.GetObject());
    }

    template <typename T> requires TriviallyIntrospectableType<T>
    ObjectHandle<RapidJsonDeserialiser::Frame> RapidJsonDeserialiser::createFrame(rapidjson::Value const &node) {
        return createHandle<ValueFrame<T>>(node);
    }

    template <typename T> requires IterableSerialisableType<T>
    ObjectHandle<RapidJsonDeserialiser::Frame> RapidJsonDeserialiser::createFrame(rapidjson::Value const &node) {
        return createHandle<ArrayFrame<T>>(node.GetArray());
    }


    bool RapidJsonDeserialiser::convertBooleanValue(std::string_view value) {
        return value == "true";
    }

    void RapidJsonDeserialiser::processSeparator() {
    }

    std::string RapidJsonDeserialiser::getFieldKey() {
        return frames.top()
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
