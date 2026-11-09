//
// Created by Admin on 9/11/2026.
//

#ifndef CPPGAME_RAPIDJSON_JSON_DESERIALISER_HPP
#define CPPGAME_RAPIDJSON_JSON_DESERIALISER_HPP

#include <stack>

#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

namespace cppengine {
    class RapidJsonDeserialiser : public Deserialiser {
    private:
        struct Frame;

        template <typename T>
        struct ValueFrame;

        struct ArrayFrame;
        struct ObjectFrame;

        template <typename T> requires NonTriviallyIntrospectableType<T>
        static ObjectHandle<Frame> createFrame(rapidjson::Value &node);

        template <typename T> requires TriviallyIntrospectableType<T>
        static ObjectHandle<Frame> createFrame(rapidjson::Value &node);

        template <typename T> requires IterableSerialisableType<T>
        static ObjectHandle<Frame> createFrame(rapidjson::Value &node);

        rapidjson::IStreamWrapper wrapper;
        rapidjson::Document document;
        std::stack<ObjectHandle<Frame>> frames;

    protected:
        bool convertBooleanValue(std::string_view value) override;

        void processSeparator() override;

        std::string getFieldKey() override;

        void beginObject() override;
        void beginObject(std::string_view name) override;
        void beginObject(std::size_t at) override;
        void endObject() override;

        std::size_t beginArray() override;
        std::size_t beginArray(std::string_view name) override;
        std::size_t beginArray(std::size_t at) override;
        void endArray() override;

        void deserialiseValue(char &value) override;
        void deserialiseValue(unsigned char &value) override;
        void deserialiseValue(short &value) override;
        void deserialiseValue(unsigned short &value) override;
        void deserialiseValue(int &value) override;
        void deserialiseValue(unsigned &value) override;
        void deserialiseValue(long &value) override;
        void deserialiseValue(unsigned long &value) override;
        void deserialiseValue(long long &value) override;
        void deserialiseValue(unsigned long long &value) override;
        void deserialiseValue(float &value) override;
        void deserialiseValue(double &value) override;
        void deserialiseValue(bool &value) override;
        void deserialiseValue(std::string &value) override;

        void deserialiseValue(std::string_view name, char &value) override;
        void deserialiseValue(std::string_view name, unsigned char &value) override;
        void deserialiseValue(std::string_view name, short &value) override;
        void deserialiseValue(std::string_view name, unsigned short &value) override;
        void deserialiseValue(std::string_view name, int &value) override;
        void deserialiseValue(std::string_view name, unsigned &value) override;
        void deserialiseValue(std::string_view name, long &value) override;
        void deserialiseValue(std::string_view name, unsigned long &value) override;
        void deserialiseValue(std::string_view name, long long &value) override;
        void deserialiseValue(std::string_view name, unsigned long long &value) override;
        void deserialiseValue(std::string_view name, float &value) override;
        void deserialiseValue(std::string_view name, double &value) override;
        void deserialiseValue(std::string_view name, bool &value) override;
        void deserialiseValue(std::string_view name, std::string &value) override;

        void deserialiseValue(std::size_t at, char &value) override;
        void deserialiseValue(std::size_t at, unsigned char &value) override;
        void deserialiseValue(std::size_t at, short &value) override;
        void deserialiseValue(std::size_t at, unsigned short &value) override;
        void deserialiseValue(std::size_t at, int &value) override;
        void deserialiseValue(std::size_t at, unsigned &value) override;
        void deserialiseValue(std::size_t at, long &value) override;
        void deserialiseValue(std::size_t at, unsigned long &value) override;
        void deserialiseValue(std::size_t at, long long &value) override;
        void deserialiseValue(std::size_t at, unsigned long long &value) override;
        void deserialiseValue(std::size_t at, float &value) override;
        void deserialiseValue(std::size_t at, double &value) override;
        void deserialiseValue(std::size_t at, bool &value) override;
        void deserialiseValue(std::size_t at, std::string &value) override;

    public:

        RapidJsonDeserialiser(std::istream &is);
        ~RapidJsonDeserialiser() override;
    };
}

#endif //CPPGAME_RAPIDJSON_JSON_DESERIALISER_HPP
