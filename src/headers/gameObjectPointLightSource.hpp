#ifndef __HEADER_GAME_OBJECT_SPOT_LIGHT_SOURCE
#define __HEADER_GAME_OBJECT_SPOT_LIGHT_SOURCE

#include "renderable.hpp"
#include "gameObject.hpp"

namespace dojo {

class GameObjectPointLightSource : public GameObject, public Renderable {
public:
    GameObjectPointLightSource(glm::vec3 color = glm::vec3(1.f, 1.f, 1.f), glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));

    ~GameObjectPointLightSource();

    glm::vec3 lightColor;

    std::vector<glm::mat4> *lightViewTransforms;
    glm::mat4 lightProjectionTransform;

    std::vector<glm::mat4> getViewTransforms();
    glm::mat4 getProjectionTransform();



};

}

#endif
