#ifndef __HEADER_GAME_OBJECT_LIGHT_SOURCE
#define __HEADER_GAME_OBJECT_LIGHT_SOURCE

#include "gameObject.hpp"
#include "renderable.hpp"

namespace dojo {

class GameObjectLightSource : public GameObject, public Renderable {
    public:
        GameObjectLightSource(glm::vec3 color = glm::vec3(1.f, 1.f, 1.f),
                glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));

        ~GameObjectLightSource();

        glm::vec3 lightColor;

    protected:
};

}

#endif
