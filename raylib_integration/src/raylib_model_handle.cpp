#include "raylib_model_handle.hpp"

#include "engine.hpp"
#include "raylib_integration.hpp"

namespace {
    ::Mesh moveMesh(::Mesh &&other) {
        ::Mesh result = {};
        std::swap(result, other);
        return result;
    }
}

namespace cppengine {
    RaylibModelHandle::RaylibModelHandle(std::string const &name_, Mesh const &mesh_) : name(name_), mesh(mesh_){
        ::UploadMesh(&mesh, false);
    }

    RaylibModelHandle::RaylibModelHandle(std::string &&name_, Mesh const &mesh_) : name(std::move(name_)), mesh(mesh_) {
        ::UploadMesh(&mesh, false);
    }

    RaylibModelHandle::RaylibModelHandle(RaylibModelHandle &&other) noexcept : name(std::move(other.name)), mesh(moveMesh(std::move(other.mesh))) {

    }

    RaylibModelHandle &RaylibModelHandle::operator=(RaylibModelHandle &&other) noexcept {
        std::swap(name, other.name);
        std::swap(mesh, other.mesh);
        return *this;
    }

    std::string const &RaylibModelHandle::getName() const {
        return name;
    }

    ::Mesh const &RaylibModelHandle::getMesh() const {
        return mesh;
    }

    RaylibModelHandle::~RaylibModelHandle() {
        UnloadMesh(mesh);
    }
}
