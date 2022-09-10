#include "headers/gameObject2DCollisionBox.hpp"
#include <iostream>

namespace dojo {

GameObject2DCollisionBox::GameObject2DCollisionBox(GameObject *obj, float relativeOffsetX, float relativeOffsetY, float relativeScaleX, float relativeScaleY) {
    objPos = &(obj->pos);
    objScale = &(obj->scale);

    relativeOffset.x = relativeOffsetX;
    relativeOffset.y = relativeOffsetY;
    relativeScale.x = relativeScaleX;
    relativeScale.y = relativeScaleY;

    owner = obj;
}

GameObject2DCollisionBox::~GameObject2DCollisionBox() {
    
}

bool GameObject2DCollisionBox::checkCollision(GameObject2DCollisionBox *box) {

    float boxX, boxY, boxW, boxH;
    boxX = box->objPos->x + (box->objScale->x * box->relativeOffset.x);
    boxW = (box->objScale->x * box->relativeScale.x);
    boxY = box->objPos->y + (box->objScale->y * box->relativeOffset.y);
    boxH = (box->objScale->y * box->relativeScale.y);

    std::cout << boxX << " "
        << boxY << " "
        << boxW << " "
        << boxH << " " << std::endl;

    float thisX, thisY, thisW, thisH;
    thisX = this->objPos->x + (this->objScale->x * this->relativeOffset.x);
    thisW = (this->objScale->x * this->relativeScale.x);
    thisY = this->objPos->y + (this->objScale->y * this->relativeOffset.y);
    thisH = (this->objScale->y * this->relativeScale.y);

    std::cout << thisX << " "
        << thisY << " "
        << thisW << " "
        << thisH << " " << std::endl;

    if (boxX < thisX + thisW &&
    boxX + boxW > thisX &&
    boxY < thisY + thisH &&
    boxH + boxY > thisY) {
        return true;
    }
    return false;
}

bool GameObject2DCollisionBox::checkCollisionWithOffset(GameObject2DCollisionBox* box, float offsetx, float offsety) {

    float boxX, boxY, boxW, boxH;
    boxX = box->objPos->x + (box->objScale->x * box->relativeOffset.x);
    boxW = box->objScale->x * box->relativeScale.x;
    boxY = box->objPos->y + (box->objScale->y * box->relativeOffset.y);
    boxH = box->objScale->y * box->relativeScale.y;

    float thisX, thisY, thisW, thisH;
    thisX = this->objPos->x + (this->objScale->x * this->relativeOffset.x) + offsetx;
    thisW = (this->objScale->x * this->relativeScale.x);
    thisY = this->objPos->y + (this->objScale->y * this->relativeOffset.y) + offsety;
    thisH = (this->objScale->y * this->relativeScale.y);

    if (boxX < thisX + thisW &&
    boxX + boxW > thisX &&
    boxY < thisY + thisH &&
    boxH + boxY > thisY) {
        return true;
    }
    return false;
}

glm::vec3 GameObject2DCollisionBox::getAbsolutePos() {
    glm::vec3 absolutePos;
    absolutePos.x = this->objPos->x + (this->objScale->x * this->relativeOffset.x);
    absolutePos.y  = this->objPos->y + (this->objScale->y * this->relativeOffset.y);
    absolutePos.z = 0;
    return absolutePos;
}

glm::vec3 GameObject2DCollisionBox::getAbsoluteScale() {
    glm::vec3 absoluteScale;
    absoluteScale.x = (this->objScale->x * this->relativeScale.x);
    absoluteScale.y = (this->objScale->y * this->relativeScale.y);
    absoluteScale.z = 0;
    return absoluteScale;
}

glm::vec3 GameObject2DCollisionBox::getAbsoluteOffset() {
    glm::vec3 absoluteOffset;
    absoluteOffset.x = relativeOffset.x * objScale->x;
    absoluteOffset.y = relativeOffset.y * objScale->y;
    absoluteOffset.z = 0;
    return absoluteOffset;
}

}
