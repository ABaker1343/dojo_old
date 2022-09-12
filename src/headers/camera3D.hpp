#ifndef __HEADER_CAMERA_3D
#define __HEADER_CAMERA_3D

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gameObject.hpp"

namespace dojo {

class Camera3D : public GameObject {
    public:
        Camera3D();
        ~Camera3D();

        //glm::mat4 transform;
        glm::mat4 projection;

    private:
};

}

#endif
