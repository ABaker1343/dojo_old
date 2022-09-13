#ifndef __HEADER_GAME_OBJECT_3D_GENERIC_TEXTURED_OBJECT
#define __HEADER_GAME_OBJECT_3D_GENERIC_TEXTURED_OBJECT

#include "gameObject.hpp"
#include "renderable.hpp"

namespace dojo {

class GameObject3DGenericTexturedObject : public GameObject, public Renderable {
    public:
        GameObject3DGenericTexturedObject(std::string objectPath, std::string texturePath,
                glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
        ~GameObject3DGenericTexturedObject();

        unsigned int texture;

};

}

#endif
