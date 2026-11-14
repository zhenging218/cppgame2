#include "game.hpp"
#include "graphics/triangle_primitive.hpp"

namespace cppgame {
    using namespace cppengine;

    void TestLevel::setup() {
        auto camera = createGameObject("camera");
        auto camera_camera2d = camera.addComponent<Camera2D>();
        auto camera_transform = camera.getTransform();
        camera_transform->setPosition({0,0,1});

        auto triangle = createGameObject("triangle");
        auto triangle_primitive = triangle.addComponent<TrianglePrimitive>();
        auto triangle_component = triangle.addComponent<TestComponent>();
        auto triangle_material = triangle.addComponent<Material>();
        triangle_material.set("uniforms", std::unordered_map<std::string, Uniform>{{ShaderLocation::SHADER_DIFFUSE_COLOUR_UNIFORM, Colour{1.f, 0.f, 0.f, 1.f}}});
        triangle.getTransform()->setPosition({0,0,1});
        triangle.getTransform()->setScale({100, 100, 1});

        auto box2d = createGameObject("box2d");
        auto box2d_component = box2d.addComponent<TestComponent2>();
        auto box2d_primitive = box2d.addComponent<Box2DPrimitive>();
        auto box2d_material = box2d.addComponent<Material>();
        box2d_material.set("uniforms", std::unordered_map<std::string, Uniform>{{ShaderLocation::SHADER_DIFFUSE_COLOUR_UNIFORM, Colour{0.f, 0.f, 1.f, 1.f}}});
        auto box2d_transform = box2d.getTransform();
        box2d_transform->setPosition({200, 200, 1});
        box2d_transform->setScale({100, 100, 1});

    }
}
