//
// Created by Admin on 19/10/2026.
//

#ifndef ILLEGAL_FIELD_OPERATION_HPP
#define ILLEGAL_FIELD_OPERATION_HPP
#include <exception>

#include <string>
#include "field_descriptor.hpp"

namespace cppengine {
    class IllegalFieldOperation : public std::exception {
    private:
        std::string message;
    public:
        IllegalFieldOperation(TypeDescriptor const *owner, TypeDescriptor const *field, std::string_view name);

        [[nodiscard]] virtual char const * what() const throw() override;
        virtual ~IllegalFieldOperation() override;
    };
}

#endif //ILLEGAL_FIELD_OPERATION_HPP
