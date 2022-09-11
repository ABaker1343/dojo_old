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
    flip = &(owner->flip);
}

GameObject2DCollisionBox::~GameObject2DCollisionBox() {
    
}

bool GameObject2DCollisionBox::checkCollision(GameObject2DCollisionBox *box) {

    float boxX, boxY, boxW, boxH;
    float thisX, thisY, thisW, thisH;

    boxX = box->getAbsolutePos().x;
    boxW = box->getAbsoluteScale().x;
    boxY = box->getAbsolutePos().y;
    boxH = box->getAbsoluteScale().y;

    thisX = getAbsolutePos().x;
    thisW = getAbsoluteScale().x;
    thisY = getAbsolutePos().y;
    thisH = getAbsoluteScale().y;

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
    float thisX, thisY, thisW, thisH;

    boxX = box->getAbsolutePos().x;
    boxW = box->getAbsoluteScale().x;
    boxY = box->getAbsolutePos().y;
    boxH = box->getAbsoluteScale().y;

    thisX = getAbsolutePos().x + offsetx;
    thisW = getAbsoluteScale().x;
    thisY = getAbsolutePos().y + offsety;
    thisH = getAbsoluteScale().y;

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
    if (*flip == 0) {
        absolutePos.x = this->objPos->x + (this->objScale->x * this->relativeOffset.x);
        absolutePos.y  = this->objPos->y + (this->objScale->y * this->relativeOffset.y);
        absolutePos.z = 0;
    }
    else {
        absolutePos.x = this->objPos->x + this->objScale->x - (this->objScale->x * this->relativeScale.x);
        absolutePos.y  = this->objPos->y + (this->objScale->y * this->relativeOffset.y);
        absolutePos.z = 0;
        absolutePos.x = absolutePos.x - getAbsoluteScale().x;
    }

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
    absoluteOffset = getAbsolutePos() - *this->objPos;
    return absoluteOffset;
}

void GameObject2DCollisionBox::clampToCollider(GameObject2DCollisionBox *box, SIDE side) {
    switch (side) {
        case left:
            this->objPos->x = box->getAbsolutePos().x - this->getAbsoluteScale().x - this->getAbsoluteOffset().x;
            break;
        case right:
            this->objPos->x = box->getAbsolutePos().x + box->getAbsoluteScale().x - this->getAbsoluteOffset().y;
            break;
        case bottom:
            this->objPos->y = box->getAbsolutePos().y - this->getAbsoluteScale().y - this->getAbsoluteOffset().y;
            break;
        case top:
            this->objPos->y = box->getAbsolutePos().y + box->getAbsoluteScale().y - this->getAbsoluteOffset().y;
            break;
    }
}

}
