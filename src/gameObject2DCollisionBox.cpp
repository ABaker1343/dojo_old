#include "headers/gameObject2DCollisionBox.hpp"

namespace dojo {

GameObject2DCollisionBox::GameObject2DCollisionBox(GameObject *obj) {
    objPos = &(obj->pos);
    objScale = &(obj->scale);
}

GameObject2DCollisionBox::~GameObject2DCollisionBox() {
    
}

bool GameObject2DCollisionBox::checkCollision(GameObject2DCollisionBox *box) {
    if (box->objPos->x < this->objPos->x + this->objScale->x &&
    box->objPos->x + box->objScale->x > this->objPos->x &&
    box->objPos->y < this->objPos->y + this->objScale->y &&
    box->objScale->y + box->objPos->y > this->objPos->y) {
        return true;
    }
    return false;
}

bool GameObject2DCollisionBox::checkCollisionWithOffset(GameObject2DCollisionBox* box, float offsetx, float offsety) {
    float newx = this->objPos->x + offsetx;
    float newy = this->objPos->y + offsety;
    
    if (box->objPos->x < newx + this->objScale->x &&
    box->objPos->x + box->objScale->x > newx &&
    box->objPos->y < newy + this->objScale->y &&
    box->objScale->y + box->objPos->y > newy) {
        return true;
    }
    return false;
}

}
