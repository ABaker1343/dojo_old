#include "headers/gameObject.hpp"
#include "headers/gameObjectLightSource.hpp"
#include <glm/ext/matrix_clip_space.hpp>

namespace dojo {

GameObjectLightSource::GameObjectLightSource(glm::vec3 color,
    glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {

    lightColor = color;

    float near_plane = 1.0f, far_plane = 7.5f;
    lightProjectionTransform = glm::ortho(-10.f, 10.f, -10.f, 10.f, near_plane, far_plane);

    lightViewTransform = glm::lookAt(pos, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
}

glm::mat4 GameObjectLightSource::getProjectionTransform() {
    return lightProjectionTransform;
}

glm::mat4 GameObjectLightSource::getViewTransform() {
    return lightViewTransform;
}

}
