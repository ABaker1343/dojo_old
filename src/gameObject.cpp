#include "headers/gameObject.hpp"

namespace dojo {

GameObject::GameObject() {
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

GameObject::~GameObject() {
}

}
