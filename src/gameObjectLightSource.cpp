#include "headers/gameObject.hpp"
#include "headers/gameObjectLightSource.hpp"

namespace dojo {

GameObjectLightSource::GameObjectLightSource(glm::vec3 color,
    glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {

    lightColor = color;
}

}
