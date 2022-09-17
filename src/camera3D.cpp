#include "headers/camera3D.hpp"
#include <glm/ext/matrix_transform.hpp>

namespace dojo {

    Camera3D::Camera3D(float relativeViewPortX, float relativeViewPortY, float relativeViewPortW, float relativeViewPortH) {
        transform = glm::mat4(1.f);
        transform = glm::translate(transform, glm::vec3(0.f, 0.f, -30.f));
        glm::vec3 pos = getPos();
        transform = glm::lookAt(pos,
                glm::vec3(pos.x, pos.y, pos.z - 1),
                glm::vec3(0.f, 1.f, 0.f));

        projection = glm::perspective(
                glm::radians(45.f),
                1600.f/900.f,
                0.1f,
                100.f
            );

        viewport = RELATIVE_VIEWPORT {
            relativeViewPortX,
            relativeViewPortY,
            relativeViewPortW,
            relativeViewPortH,
        };
    }

    Camera3D::~Camera3D() {

    }

    void Camera3D::move(float x, float y, float z) {
        transform[3][0] = -x;
        transform[3][1] = -y;
        transform[3][2] = -z;
        transform[3][3] = 1;
        
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

    void Camera3D::rotate(float degrees, glm::vec3 axis) {
        glm::vec3 pos = getPos();
        /*transform = glm::lookAt(
                pos,
                glm::vec3(pos.x + glm::cos(glm::radians(degrees)) * axis.x, pos.y + glm::sin(glm::radians(degrees)) * axis.y, 0),
                glm::vec3(0.f, 1.f, 0.f)
                );*/

        move(0.f, 0.f, 0.f);
        transform = glm::rotate(transform, glm::radians(degrees), axis);
        move(0 + pos.x, 0 + pos.y, 0 + pos.z);
    }

}
