//
// Created by Admin on 19/10/2026.
//

#ifndef SCENE_HELPER_HPP
#define SCENE_HELPER_HPP

namespace cppengine {
    template <typename T>
    concept ComponentType = std::is_base_of_v<Component, T>;

    template <typename T>
    concept TransformType = std::is_same_v<Transform, T>;
}

#endif //SCENE_HELPER_HPP
