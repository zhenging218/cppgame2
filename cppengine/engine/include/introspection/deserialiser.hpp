#ifndef DESERIALISER_HPP
#define DESERIALISER_HPP

#include "reflection/type_descriptor.hpp"
#include "introspection_traits.hpp"

namespace cppengine {
    class Deserialiser {
    private:

    protected:


    public:

        template <typename T>
        void deserialise(T &dest);

        virtual ~Deserialiser() = 0;
    };

    inline Deserialiser::~Deserialiser() = default;
}

#endif