#ifndef __HEADER_GAME_OBJECT_2D_SPRITE
#define __HEADER_GAME_OBJECT_2D_SPRITE

#include "gameObject.hpp"
#include "renderable.hpp"

namespace dojo {

class GameObject2DSprite : public GameObject, public Renderable {
    public:
        GameObject2DSprite(std::string spritePath, glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f),
                unsigned int VertexArrayObject = 0, unsigned int shaderProgram = 0);
        GameObject2DSprite(unsigned int texture, unsigned int VertexArrayObject = 0, unsigned int shaderProgram = 0,
                glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
        GameObject2DSprite(GameObject2DSprite *obj, glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
        ~GameObject2DSprite();

        unsigned int texture;

    private:
        bool isCopy;

};

}

#endif
