#ifndef __HEADER_GAME_OBJECT_LIGHT_SOURCE
#define __HEADER_GAME_OBJECT_LIGHT_SOURCE

#include "gameObject.hpp"
#include "renderable.hpp"

namespace dojo {

class GameObjectLightSource : public GameObject, public Renderable {
    public:
        GameObjectLightSource();

        ~GameObjectLightSource();

        glm::vec3 lightColor;

    protected:
};

}

#endif
