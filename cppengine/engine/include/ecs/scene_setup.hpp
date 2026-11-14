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
        SceneSetup const *sceneSetup;

        GameObjectProxy(std::uint64_t id_, SceneSetup const *sceneSetup_);
    public:
        template <typename T, typename ... Args> requires ComponentType<T>
        ComponentProxy<T> addComponent(Args &&... args) const;

        template <typename T> requires ComponentType<T>
        [[nodiscard]] ComponentProxy<T> getComponent() const;

        [[nodiscard]] ObjectHandle<Transform> getTransform() const;
        [[nodiscard]] std::string_view getName() const;
    };

    template<typename T> requires ComponentType<T>
    class ComponentProxy {
    private:
        friend class GameObjectProxy;

        std::uint64_t owner;
        ObjectHandle<T> component;
        SceneSetup const *sceneSetup;

        ComponentProxy(std::uint64_t owner_, ObjectHandle<T> component_, SceneSetup const * sceneSetup_);
    public:
        [[nodiscard]] GameObjectProxy getGameObject() const;

        template <typename U>
        void set(std::string_view fieldName, U &&value) const;
    };

    class SceneSetup {
    private:
        friend class SceneManager;
        friend class GameObjectProxy;

        template <typename T> requires ComponentType<T>
        friend class ComponentProxy;

        Scene *scene = nullptr;

        void setScene(Scene *scene_);
    protected:
        [[nodiscard]] GameObjectProxy createGameObject() const;
        [[nodiscard]] GameObjectProxy createGameObject(std::string_view name) const;

    public:
        virtual void setup() = 0;
        virtual ~SceneSetup() = 0;
    };

    template <typename T>
    concept SceneSetupType = std::derived_from<T, SceneSetup>;
}

#endif //CPPGAME_SCENE_SETUP_HPP
