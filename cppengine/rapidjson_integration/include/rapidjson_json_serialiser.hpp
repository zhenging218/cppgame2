//
// Created by Admin on 8/11/2026.
//

#ifndef CPPGAME_RAPIDJSON_SERIALISER_HPP
#define CPPGAME_RAPIDJSON_SERIALISER_HPP

#include "rapidjson/writer.h"
#include "rapidjson/ostreamwrapper.h"

namespace cppengine {
    class RapidJsonSerialiser : public Serialiser {
    private:
        rapidjson::OStreamWrapper wrapper;
        rapidjson::Writer<rapidjson::OStreamWrapper> writer;

    protected:
        void beginObject(std::string_view name) override;
        void beginObject() override;
        void endObject() override;

        void beginArray(std::string_view name) override;
        void beginArray() override;
        void endArray() override;

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
        void serialiseValue(std::string_view value) override;

        void serialiseValue(std::string_view name, const char &value) override;
        void serialiseValue(std::string_view name, const unsigned char &value) override;
        void serialiseValue(std::string_view name, const short &value) override;
        void serialiseValue(std::string_view name, const unsigned short &value) override;
        void serialiseValue(std::string_view name, const int &value) override;
        void serialiseValue(std::string_view name, const unsigned &value) override;
        void serialiseValue(std::string_view name, const long &value) override;
        void serialiseValue(std::string_view name, const unsigned long &value) override;
        void serialiseValue(std::string_view name, const long long &value) override;
        void serialiseValue(std::string_view name, const unsigned long long &value) override;
        void serialiseValue(std::string_view name, const float &value) override;
        void serialiseValue(std::string_view name, const double &value) override;
        void serialiseValue(std::string_view name, const bool &value) override;
        void serialiseValue(std::string_view name, std::string_view value) override;

        void processSeparator() override;

    public:

        RapidJsonSerialiser(std::ostream &os);
        ~RapidJsonSerialiser() override;
    };
}

#endif //CPPGAME_RAPIDJSON_SERIALISER_HPP
