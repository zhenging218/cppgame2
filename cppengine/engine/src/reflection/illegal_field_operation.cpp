//
// Created by Admin on 19/10/2026.
//

#include "engine.hpp"

namespace cppengine {
    IllegalFieldOperation::IllegalFieldOperation(TypeDescriptor const *owner, TypeDescriptor const *field, std::string_view name)
        : message(std::format("Illegal field operation performed on {2} {0}::{1}", owner->getName(), name, field->getName())){

    }

    char const * IllegalFieldOperation::what() const throw() {
        return message.c_str();
    }

    IllegalFieldOperation::~IllegalFieldOperation() {}
}
