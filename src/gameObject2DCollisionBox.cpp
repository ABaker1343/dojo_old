#include "headers/gameObject2DCollisionBox.hpp"
#include <iostream>

namespace dojo {

GameObject2DCollisionBox::GameObject2DCollisionBox(GameObject *obj, float relativeOffsetX, float relativeOffsetY, float relativeScaleX, float relativeScaleY) {
    //objPos = &(obj->pos);
    //objScale = &(obj->scale);

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

    //opengl uses column major:
    //mat[col][row]

    glm::vec3 absolutePos;

    auto ownerPos = this->owner->getPos();
    auto ownerScale = this->owner->getScale();

    if (*flip == 0) {
        absolutePos.x = ownerPos.x + (ownerScale.x * this->relativeOffset.x);
        absolutePos.y = ownerPos.y + (ownerScale.y * this->relativeOffset.y);
        absolutePos.z = ownerPos.z + (ownerScale.z * this->relativeOffset.z);
    } else {
        absolutePos.x = ownerPos.x + ownerScale.x - (ownerScale.x * this->relativeScale.x);
        absolutePos.y = ownerPos.y + (ownerScale.y * this->relativeOffset.y);
        absolutePos.z = ownerPos.z + (ownerScale.z * this->relativeOffset.z);

        //ownerback - offset - boxScale;
        absolutePos.x = (ownerPos.x + ownerScale.x) - (ownerScale.x * relativeOffset.x) - (ownerScale.x * relativeScale.x);
    }

    return absolutePos;


}

glm::vec3 GameObject2DCollisionBox::getAbsoluteScale() {
    glm::vec3 absoluteScale;

    absoluteScale.x = this->owner->getScale().x * this->relativeScale.x;
    absoluteScale.y = this->owner->getScale().y * this->relativeScale.y;
    absoluteScale.z = this->owner->getScale().z;

    return absoluteScale;
}

glm::vec3 GameObject2DCollisionBox::getAbsoluteOffset() {
    glm::vec3 absoluteOffset;
    absoluteOffset = getAbsolutePos() - this->owner->getPos();
    return absoluteOffset;
}

void GameObject2DCollisionBox::clampToCollider(GameObject2DCollisionBox *box, SIDE side) {
    switch (side) {
        case left:
            this->owner->transform[3][0] = box->getAbsolutePos().x - this->getAbsoluteScale().x - this->getAbsoluteOffset().x;
            break;
        case right:
            this->owner->transform[3][0] = box->getAbsolutePos().x + box->getAbsoluteScale().x - this->getAbsoluteOffset().x;
            break;
        case bottom:
            this->owner->transform[3][1] = box->getAbsolutePos().y - this->getAbsoluteScale().y - this->getAbsoluteOffset().y;
            break;
        case top:
            this->owner->transform[3][1] = box->getAbsolutePos().y + box->getAbsoluteScale().y - this->getAbsoluteOffset().y;
            break;
    }
}

glm::mat4 GameObject2DCollisionBox::getTransform() {
    glm::mat4 transform = owner->transform;
    transform = glm::translate(transform, getAbsoluteOffset());
    transform = glm::scale(transform, relativeScale);

    transform = glm::mat4(1.f);
    transform = glm::translate(transform, glm::vec3(getAbsolutePos()));
    transform = glm::scale(transform, getAbsoluteScale());
    return transform;

}

void GameObject2DCollisionBox::attachCollisionCallback(GameObject2DCollisionBox *box, void *func) {
    callbackColliders->insert({box, func});
}

}
