#include "gameObject.hpp"

namespace dojo {

class GameObject2DCollisionBox {
    public :
        GameObject2DCollisionBox(GameObject *obj);
        ~GameObject2DCollisionBox();

        bool checkCollision(GameObject2DCollisionBox* box);

    private:
        glm::vec3 *objPos;
        glm::vec3 *objScale;
};

}
