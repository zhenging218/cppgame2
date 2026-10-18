#include "engine.hpp"

namespace cppengine {
    TypeDescriptor::~TypeDescriptor() {}

    bool TypeDescriptor::isSuperType(TypeDescriptor const *superType, TypeDescriptor const *subType) {
        if (superType == subType) {
            return true;
        }

        while (subType != superType && subType->getSuperType() != subType) {
            subType = subType->getSuperType();
            if (superType == subType) {
                return true;
            }
        }
        return false;
    }
}
