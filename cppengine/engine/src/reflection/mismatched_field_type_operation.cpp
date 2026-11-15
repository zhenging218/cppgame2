//
// Created by Admin on 14/11/2026.
//

#include "engine.hpp"

namespace cppengine {
    MismatchedFieldTypeOperation::MismatchedFieldTypeOperation(TypeDescriptor const *owner, TypeDescriptor const *field, std::string_view fieldName)
        : message(std::format("Field type mismatch: Type {} does not have field with name {} of type {}", owner->getName(), fieldName, field->getName())){

    }

    char const *MismatchedFieldTypeOperation::what() const noexcept {
        return message.c_str();
    }

    MismatchedFieldTypeOperation::~MismatchedFieldTypeOperation() = default;
}
