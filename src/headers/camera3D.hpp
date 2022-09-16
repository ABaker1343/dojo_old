#ifndef __HEADER_CAMERA_3D
#define __HEADER_CAMERA_3D

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gameObject.hpp"

namespace dojo {

class Camera3D : public GameObject {
    public:
        Camera3D(float relativeViewPortX = 0.f, float relativeViewPortY = 0.f, float relativeViewPortW = 1.0f, float relativeViewPortH = 1.0f);
        ~Camera3D();

        typedef struct RELATIVE_VIEWPORT_STRUCT {
            float x;
            float y;
            float w;
            float h;
        } RELATIVE_VIEWPORT;

        RELATIVE_VIEWPORT viewport;

        //glm::mat4 transform;
        glm::mat4 projection;

        //glm::vec3 pos;
        //glm::vec3 target;

        void move(float x, float y, float z = 0.f);
        glm::vec3 getPos();

        glm::mat4 getProjectionTransform();


    private:
};

}

#endif
