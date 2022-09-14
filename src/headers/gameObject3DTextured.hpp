#ifndef __HEADER_GAME_OBJECT_3D_GENERIC_TEXTURED_OBJECT
#define __HEADER_GAME_OBJECT_3D_GENERIC_TEXTURED_OBJECT

#include "gameObject.hpp"
#include "renderable.hpp"

namespace dojo {

class GameObject3DTextured : public GameObject, public Renderable {
    public:

        typedef enum SHAPES_ENUM {
            cube,
        } Shape;

        GameObject3DTextured(Shape shape, std::string texture,
                glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
        GameObject3DTextured(std::string objectPath, std::string texturePath,
                glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
        GameObject3DTextured(GameObject3DTextured* obj,
                glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));

        ~GameObject3DTextured();

        unsigned int texture;

    protected:
        bool isClone;

        void createCubeVertices(unsigned int &textureOffset, unsigned int &normalOffset);

};

}

#endif
