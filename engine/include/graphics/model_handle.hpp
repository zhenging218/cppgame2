#ifndef MODEL_HANDLE_HPP
#define MODEL_HANDLE_HPP

namespace cppengine {
    class ModelHandle {
    private:

    public:
        virtual ~ModelHandle() = 0;
    };

    inline ModelHandle::~ModelHandle() = default;
}

#endif