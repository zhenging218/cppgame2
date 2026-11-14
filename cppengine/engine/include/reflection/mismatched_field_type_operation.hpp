//
// Created by Admin on 14/11/2026.
//

#ifndef CPPGAME_MISMATCHEDFIELDTYPEOPERATION_HPP
#define CPPGAME_MISMATCHEDFIELDTYPEOPERATION_HPP

namespace cppengine {
    class MismatchedFieldTypeOperation : public std::exception {
    private:
        std::string message;
    public:
        MismatchedFieldTypeOperation(TypeDescriptor const *owner, TypeDescriptor const *field, std::string_view fieldName);

        [[nodiscard]] char const * what() const noexcept override;
        ~MismatchedFieldTypeOperation() override;
    };
}

#endif //CPPGAME_MISMATCHEDFIELDTYPEOPERATION_HPP
