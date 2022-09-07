#include "headers/camera2D.hpp"

namespace dojo {

    Camera2D::Camera2D() {
        pos = glm::vec3(0.0f, 0.0f, 0.0f);
        scale = glm::vec3(50.0f, 50.0f, 0.0f);
    }

    Camera2D::~Camera2D() {

    }

}
