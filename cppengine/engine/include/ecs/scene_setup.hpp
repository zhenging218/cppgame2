//
// Created by Admin on 2/11/2026.
//

#ifndef CPPGAME_SCENE_SETUP_HPP
#define CPPGAME_SCENE_SETUP_HPP

namespace cppengine {

    class Scene;
    class SceneSetup;

    template <typename T> requires ComponentType<T>
    class ComponentProxy;

    class GameObjectProxy {
    private:
        friend class SceneSetup;

        template <typename T> requires ComponentType<T>
        friend class ComponentProxy;

        std::uint64_t id;
        SceneSetup *sceneSetup;

        GameObjectProxy(std::uint64_t id_, SceneSetup *sceneSetup_);
    public:
        template <typename T, typename ... Args> requires ComponentType<T>
        ComponentProxy<T> addComponent(Args &&... args) const;

        template <typename T> requires ComponentType<T>
        ComponentProxy<T> getComponent() const;

        [[nodiscard]] ObjectHandle<Transform> getTransform() const;
        [[nodiscard]] std::string_view getName() const;
    };

    template<typename T> requires ComponentType<T>
    class ComponentProxy {
    private:
        std::uint64_t owner;
        ObjectHandle<T> component;
        SceneSetup *sceneSetup;

        ComponentProxy(std::uint64_t owner_, ObjectHandle<T> component_, SceneSetup * sceneSetup_);
    public:
        GameObjectProxy getGameObject() const;

        T& operator*() const;
        T * operator->() const;
    };



    class SceneSetup {
    private:
        friend class GameObjectProxy;

        template <typename T> requires ComponentType<T>
        friend class ComponentProxy;

        Scene *scene;

        explicit SceneSetup(Scene *scene_);
    protected:
        GameObjectProxy createGameObject() const;
        GameObjectProxy createGameObject(std::string_view name) const;

    public:
        virtual void setup() = 0;

        virtual ~SceneSetup() = 0;
    };
}

#endif //CPPGAME_SCENE_SETUP_HPP
