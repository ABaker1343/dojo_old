#include "headers/camera3D.hpp"
#include <glm/ext/matrix_transform.hpp>

namespace dojo {

    Camera3D::Camera3D(glm::vec3 pos) {
        projection = glm::perspective(
                glm::radians(45.f),
                1600.f/900.f,
                0.1f,
                100.f
            );

        cameraPos = pos;
        cameraFront = glm::vec3(0.f, 0.f, -1.f);
        cameraUp = glm::vec3(0.f, 1.f, 0.f);

        transform = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        viewport = RELATIVE_VIEWPORT {0, 0, 1.f, 1.f};
    }

    Camera3D::~Camera3D() {

    }

    void Camera3D::setViewPort(float relativex, float relativey, float relativew, float relativeh) {
        viewport = RELATIVE_VIEWPORT {
            relativex,
            relativey,
            relativew,
            relativeh,
        };
    }

    void Camera3D::move(float x, float y, float z) {
        cameraPos.x = x;
        cameraPos.y = y;
        cameraPos.z = z;
    }

    glm::vec3 Camera3D::getPos() {
        return cameraPos;
    }

    glm::mat4 Camera3D::getProjectionTransform(){
        return projection;
    }

    void Camera3D::rotate(float degrees, glm::vec3 axis) {
        cameraFront = glm::rotate(cameraFront, glm::radians(degrees), axis);
    }

    glm::mat4 Camera3D::getTransform() {
        return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }

}
