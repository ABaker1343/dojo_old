#ifndef __HEADER_GAME_OBJECT_3D_CUBE
#define __HEADER_GAME_OBJECT_3D_CUBE

#include "gameObject.hpp"
#include "renderable.hpp"

namespace dojo {

class GameObject3DCube : public GameObject, public Renderable {
    public:
        GameObject3DCube(std::string texturePath, glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
        ~GameObject3DCube();

        unsigned int texture;

};

}

#endif
