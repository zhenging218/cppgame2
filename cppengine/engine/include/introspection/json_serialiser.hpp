//
// Created by Admin on 8/11/2026.
//

#ifndef CPPGAME_JSON_SERIALISER_HPP
#define CPPGAME_JSON_SERIALISER_HPP
#include "memory/object_handle.hpp"

namespace cppengine::JsonSerialiser {
    ObjectHandle<Serialiser> createSerialiser(std::ostream &stream);

}


#endif //CPPGAME_JSON_SERIALISER_HPP
