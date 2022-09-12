#include "headers/gameObject.hpp"

namespace dojo {

GameObject::GameObject() {
    transform = glm::mat4(1.0f);

    flip = 0;
}

GameObject::~GameObject() {
}

void GameObject::setPos(float x, float y, float z) {
    transform[3][0] = x;
    transform[3][1] = y;
    transform[3][2] = z;
    transform[3][3] = 1.f;
}

glm::vec3 GameObject::getPos() {
    glm::vec3 pos;
    pos.x = transform[3][0];
    pos.y = transform[3][1];
    pos.z = transform[3][2];
    return pos;
}

void GameObject::setScale(float x, float y, float z) {
    transform[0][0] = x;
    transform[1][1] = y;
    transform[2][2] = z;
    transform[3][3] = 1.f;
}

glm::vec3 GameObject::getScale() {
    glm::vec3 scale;
    scale.x = transform[0][0];
    scale.y = transform[1][1];
    scale.z = transform[2][2];
    return scale;
}

}
