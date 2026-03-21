#ifndef SERIALISER_HPP
#define SERIALISER_HPP

#include <cstdint>

namespace cppengine {

    class Serialiser;

    template <typename T>
    concept SerialisableType = requires(T const & t, Serialiser &r) { { t.serialise(r) } -> std::same_as<void>; };

    class Serialiser {
    private:
        template <typename ... Visitor>
        struct Visitors : Visitor... {
            using Visitor::operator()...;
        };

        template <typename Visitor, typename ... T>
        void serialiseObject(ArgumentList<T...> args, Visitor &&v) {
            (v(T{}), ...);
        }

        template <typename T>
        void serialise(std::string_view name, T const &object);

    protected:
        virtual void beginObject(std::string_view name) = 0;

        virtual void serialise(std::string_view name, char const &value) = 0;
        virtual void serialise(std::string_view name, unsigned char const &value) = 0;
        virtual void serialise(std::string_view name, short const &value) = 0;
        virtual void serialise(std::string_view name, unsigned short const &value) = 0;
        virtual void serialise(std::string_view name, int const &value) = 0;
        virtual void serialise(std::string_view name, unsigned int const &value) = 0;
        virtual void serialise(std::string_view name, long const &value) = 0;
        virtual void serialise(std::string_view name, unsigned long const &value) = 0;
        virtual void serialise(std::string_view name, long long const &value) = 0;
        virtual void serialise(std::string_view name, unsigned long long const &value) = 0;
        virtual void serialise(std::string_view name, float const &value) = 0;
        virtual void serialise(std::string_view name, double const &value) = 0;
        virtual void serialise(std::string_view name, bool const &value) = 0;
        virtual void serialise(std::string_view name, std::string const &value) = 0;

        virtual void endObject() = 0;

    public:

        template <typename T>
        void serialise(T const &src);

        virtual ~Serialiser() = 0;
    };

    inline Serialiser::~Serialiser() = default;
}

#endif