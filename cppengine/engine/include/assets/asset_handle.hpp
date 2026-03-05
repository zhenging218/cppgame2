#ifndef ASSET_HANDLE_HPP
#define ASSET_HANDLE_HPP

namespace cppengine {
    class AssetHandle {
    private:

    public:
        virtual ~AssetHandle() = 0;
    };

    inline AssetHandle::~AssetHandle() = default;
}

#endif