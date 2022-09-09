#include "gameObject.hpp"

namespace dojo {

class GameObject2DCollisionBox {
    public :
        GameObject2DCollisionBox(GameObject *obj);
        ~GameObject2DCollisionBox();

        bool checkCollision(GameObject2DCollisionBox* box);
        bool checkCollisionWithOffset(GameObject2DCollisionBox* box, float offsetx, float offsety);

        glm::vec3 *objPos;
        glm::vec3 *objScale;
};

}
