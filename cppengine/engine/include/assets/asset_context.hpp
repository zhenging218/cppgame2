#ifndef ASSET_CONTEXT_HPP
#define ASSET_CONTEXT_HPP

namespace cppengine {
    class AssetContext {
    private:

    public:

        virtual ~AssetContext() = 0;
    };

    inline AssetContext::~AssetContext() = default;
}

#endif