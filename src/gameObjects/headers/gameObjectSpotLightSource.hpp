#ifndef __HEADER_GAME_OBJECT_LIGHT_SOURCE
#define __HEADER_GAME_OBJECT_LIGHT_SOURCE

#include "gameObject.hpp"
#include "../../headers/renderable.hpp"

namespace dojo {

class GameObjectSpotLightSource : public GameObject, public Renderable {
    public:
        GameObjectSpotLightSource(glm::vec3 target, glm::vec3 color = glm::vec3(1.f, 1.f, 1.f),
                glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));

        ~GameObjectSpotLightSource();

        glm::vec3 lightColor;
        glm::vec3 m_target;

        glm::mat4 lightProjectionTransform;
        glm::mat4 lightViewTransform;

        glm::mat4 getProjectionTransform();
        glm::mat4 getViewTransform();

    protected:
};

}

#endif
