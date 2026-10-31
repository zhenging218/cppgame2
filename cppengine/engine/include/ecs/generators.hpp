//
// Created by Admin on 31/10/2026.
//

#ifndef CPPGAME_GENERATORS_HPP
#include <cstdint>

namespace cppengine {
    class IdGenerator {
    private:

    public:

        virtual std::uint64_t unidentified() const = 0;
        virtual std::uint64_t next() = 0;
        virtual std::uint64_t curr() = 0;
        virtual ~IdGenerator() = 0;
    };

    class CycleGenerator {
    private:

    public:

        virtual std::uint64_t next() = 0;
        virtual std::uint64_t curr() = 0;
        virtual ~CycleGenerator() = 0;
    };
}

#define CPPGAME_GENERATORS_HPP

#endif //CPPGAME_GENERATORS_HPP
