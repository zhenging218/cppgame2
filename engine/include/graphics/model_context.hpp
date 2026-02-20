#ifndef MODEL_CONTEXT_HPP
#define MODEL_CONTEXT_HPP

namespace cppengine {
    class ModelContext {
    private:

    public:
        virtual ~ModelContext() = 0;
    };

    inline ModelContext::~ModelContext() = default;
}

#endif