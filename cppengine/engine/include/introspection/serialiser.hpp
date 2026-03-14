#ifndef SERIALISER_HPP
#define SERIALISER_HPP

#include <cstdint>

namespace cppengine {

    class Serialiser;

    template <typename T>
    concept SerialisableType = requires(T const & t, Serialiser &r) { { t.serialise(r) } -> std::same_as<void>; };

    class Serialiser {
    private:


    protected:
        virtual void beginObject() = 0;

        virtual void serialise(char const &value) = 0;
        virtual void serialise(unsigned char const &value) = 0;
        virtual void serialise(short const &value) = 0;
        virtual void serialise(unsigned short const &value) = 0;
        virtual void serialise(int const &value) = 0;
        virtual void serialise(unsigned int const &value) = 0;
        virtual void serialise(long const &value) = 0;
        virtual void serialise(unsigned long const &value) = 0;
        virtual void serialise(long long const &value) = 0;
        virtual void serialise(unsigned long long const &value) = 0;
        virtual void serialise(float const &value) = 0;
        virtual void serialise(double const &value) = 0;
        virtual void serialise(bool const &value) = 0;

        virtual void endObject() = 0;

    public:

        template <typename T>
        void serialise(T const &src, Serialiser &r);

        virtual ~Serialiser() = 0;
    };

    inline Serialiser::~Serialiser() = default;
}

#endif