#ifndef __HEADER_CAMERA_3D
#define __HEADER_CAMERA_3D

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "gameObject.hpp"

namespace dojo {

class Camera3D : public GameObject {
    public:
        Camera3D(glm::vec3 pos = glm::vec3(0.f, 5.f, 50.f));
        ~Camera3D();

        typedef struct RELATIVE_VIEWPORT_STRUCT {
            float x;
            float y;
            float w;
            float h;
        } RELATIVE_VIEWPORT;

        RELATIVE_VIEWPORT viewport;

        glm::mat4 projection;

        void setViewPort(float relativex, float relativey, float relativew, float relativeh);

        void move(float x, float y, float z = 0.f);
        glm::vec3 getPos();

        void rotate(float degrees, glm::vec3 axis);

        glm::mat4 getProjectionTransform();
        glm::mat4 getTransform();


    private:
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;

};

}

#endif
