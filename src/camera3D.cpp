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

    void Camera3D::move(float x, float y, float z) {
        transform[3][0] = -x;
        transform[3][1] = -y;
        transform[3][2] = -z;

        //transform = glm::lookAt(pos, target, glm::vec3(0.f, 0.f, 1.f));
        //transform = glm::translate(transform, glm::vec3(-x, -y, -z));
    }

    glm::vec3 Camera3D::getPos() {
        glm::vec3 pos;
        pos.x = -transform[3][0];
        pos.y = -transform[3][1];
        pos.z = -transform[3][2];
        return pos;
    }

    glm::mat4 Camera3D::getProjectionTransform(){
        return projection;
    }

}
