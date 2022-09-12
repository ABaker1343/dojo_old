#include "headers/camera3D.hpp"
#include <glm/ext/matrix_transform.hpp>

namespace dojo {

    Camera3D::Camera3D() {
        transform = glm::mat4(1.f);
        transform = glm::translate(transform, glm::vec3(0.f, 0.f, -30.f));

        projection = glm::perspective(
                glm::radians(45.f),
                1600.f/900.f,
                0.1f,
                100.f
            );
    }

    Camera3D::~Camera3D() {

    }

}
