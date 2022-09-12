#ifndef __HEADER_GAME_OBJECT_2D_COLLISION_BOX
#define __HEADER_GAME_OBJECT_2D_COLLISION_BOX

#include "gameObject.hpp"

namespace dojo {

class GameObject2DCollisionBox {
    public :
        GameObject2DCollisionBox(GameObject *obj, float relativeOffsetX = 0.f, float relativeOffsetY = 0.f, float relativeScaleX = 1.f, float relativeScaleY = 1.f);
        ~GameObject2DCollisionBox();

        typedef enum SIDE_ENUM {left, right, top, bottom} SIDE;

        bool checkCollision(GameObject2DCollisionBox* box);
        bool checkCollisionWithOffset(GameObject2DCollisionBox* box, float offsetx, float offsety);

        int *flip;

        glm::vec3 getAbsolutePos();
        glm::vec3 getAbsoluteScale();
        glm::vec3 getAbsoluteOffset();
        glm::mat4 getTransform();

        void clampToCollider(GameObject2DCollisionBox *box, SIDE side);

        glm::vec3 relativeOffset;
        glm::vec3 relativeScale;

        GameObject *owner;
        //glm::vec3 *objPos;
        //glm::vec3 *objScale;

};

}

#endif
