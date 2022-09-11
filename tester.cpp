#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>

#include "src/headers/camera2D.hpp"
#include "src/headers/dojo.hpp"
#include "src/headers/gameObject2DAnimatedSprite.hpp"
#include "src/headers/gameObject.hpp"
#include "src/headers/gameObject2DSprite.hpp"
#include "src/headers/window.hpp"

typedef struct INPUT_HANDLER_INPUTS {
    dojo::Window* window;
    dojo::GameObject2DAnimatedSprite *sprite;
    dojo::Camera2D *camera;
    dojo::GameObject2DCollisionBox *spriteCollider;
    dojo::GameObject2DCollisionBox *cameraCollider;
    std::vector<dojo::GameObject2DCollisionBox*> *collisionBoxes;
} HANDLER_INPUT;

void handleInputs(HANDLER_INPUT*);

int main () {

    srand(time(NULL));

    dojo::Window *window = new dojo::Window(500, 500, "dojoWindow");

    //dojo::GameObject2DSprite *player = new dojo::GameObject2DSprite("bgCatAndSakura.jpg");
    dojo::GameObject2DAnimatedSprite *player = new dojo::GameObject2DAnimatedSprite(4, "animation0.jpg");
    player->addAnimation("walking", 4, "makima.jpg");
    player->scale.x = 5; player->scale.y = 5;

    dojo::Camera2D *c = new dojo::Camera2D();

    //dojo::GameObject2DCollisionBox *playerCollider = new dojo::GameObject2DCollisionBox(player);
    dojo::GameObject2DCollisionBox *playerCollider = new dojo::GameObject2DCollisionBox(player, 0.5f, 0.5f, 0.5f, 0.5f);
    dojo::GameObject2DCollisionBox *cameraCollider = new dojo::GameObject2DCollisionBox(c);

    std::vector<dojo::GameObject2DSprite*> *objects = new std::vector<dojo::GameObject2DSprite*>;
    std::vector<dojo::GameObject2DCollisionBox*> *colliders = new std::vector<dojo::GameObject2DCollisionBox*>;
    
    dojo::GameObject2DSprite *initialSprite = new dojo::GameObject2DSprite("texture.png");
    initialSprite->pos.x = rand() % (int)c->scale.x;
    initialSprite->pos.y = rand() % (int)c->scale.y;
    dojo::GameObject2DCollisionBox *initialCollider = new dojo::GameObject2DCollisionBox(initialSprite);
    objects->push_back(initialSprite);
    colliders->push_back(initialCollider);


    for (int i = 0; i < 10; i++) {
        dojo::GameObject2DSprite *newObj = new dojo::GameObject2DSprite(initialSprite);
        newObj->pos.x = rand() % (int)c->scale.x;
        newObj->pos.y = rand() % (int)c->scale.y;
        dojo::GameObject2DCollisionBox *newCollider = new dojo::GameObject2DCollisionBox(newObj);
        objects->push_back(newObj);
        colliders->push_back(newCollider);
    }

    HANDLER_INPUT hinputs;
    hinputs.sprite = player;
    hinputs.cameraCollider = cameraCollider;
    hinputs.spriteCollider = playerCollider;
    hinputs.window = window;
    hinputs.camera = c;
    hinputs.collisionBoxes = colliders;

    std::chrono::duration<double> frametime = std::chrono::milliseconds(50);

    while (window->isAlive()) {
        auto start = std::chrono::system_clock::now();

        handleInputs(&hinputs);
        window->clear();
        for (std::vector<dojo::GameObject2DSprite*>::iterator it = objects->begin(); it != objects->end(); it++){
            window->render2D(c, *it);
        }
        window->render2D(c, player);
        for (std::vector<dojo::GameObject2DCollisionBox*>::iterator it = colliders->begin(); it != colliders->end(); it++) {
            window->render2D(c, *it);
        }
        window->render2D(c, playerCollider);
        if (!player->nextFrame()) {
            if (player->currentAnimationName() == "default") {
                player->setCurrentAnimation("walking");
            } else {
                player->setCurrentAnimation("default");
            }
        }

        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> timeTaken = end - start;
        
        if (timeTaken < frametime ) {
            std::this_thread::sleep_for(frametime - timeTaken);
        }
    }

    delete window;
    delete player;
    delete c;

    for (std::vector<dojo::GameObject2DSprite*>::iterator it = objects->begin(); it != objects->end(); it++) {
        delete *it;
    }
    for (std::vector<dojo::GameObject2DCollisionBox*>::iterator it = colliders->begin(); it != colliders->end(); it++) {
        delete *it;
    }

    delete objects;
    delete colliders;

    return 0;
}

void handleInputs(HANDLER_INPUT *hinput) {
    if (hinput->window->KEYS[GLFW_KEY_A]) {
        bool colliding = false;
        for (std::vector<dojo::GameObject2DCollisionBox*>::iterator it = hinput->collisionBoxes->begin(); it != hinput->collisionBoxes->end(); it++)  {
            if (hinput->spriteCollider->checkCollisionWithOffset(*it, -1.f, 0.f)) {
                colliding = true;
                hinput->spriteCollider->clampToCollider(*it, dojo::GameObject2DCollisionBox::right);
                break;
            }
        }
        if (!colliding) {
            hinput->sprite->pos.x --;
        }
        if (hinput->spriteCollider->getAbsolutePos().x < hinput->cameraCollider->getAbsolutePos().x) {
            hinput->sprite->pos.x = hinput->cameraCollider->getAbsolutePos().x - (hinput->spriteCollider->getAbsoluteOffset().x);
        }
    }
    if (hinput->window->KEYS[GLFW_KEY_D]) {
        bool colliding = false;
        for (std::vector<dojo::GameObject2DCollisionBox*>::iterator it = hinput->collisionBoxes->begin(); it != hinput->collisionBoxes->end(); it++)  {
            if (hinput->spriteCollider->checkCollisionWithOffset(*it, 1.f, 0.f)) {
                colliding = true;
                hinput->spriteCollider->clampToCollider(*it, dojo::GameObject2DCollisionBox::left);
                break;
            }
        }
        if (!colliding) {
            hinput->sprite->pos.x ++;
        }
        if (hinput->spriteCollider->getAbsolutePos().x + hinput->spriteCollider->getAbsoluteScale().x > hinput->cameraCollider->getAbsolutePos().x + hinput->cameraCollider->getAbsoluteScale().x) {
            hinput->sprite->pos.x = hinput->cameraCollider->getAbsolutePos().x + hinput->cameraCollider->getAbsoluteScale().x - (hinput->spriteCollider->getAbsoluteScale().x + hinput->spriteCollider->getAbsoluteOffset().x);
        }
    }
    if (hinput->window->KEYS[GLFW_KEY_W]) {
        bool colliding = false;
        for (std::vector<dojo::GameObject2DCollisionBox*>::iterator it = hinput->collisionBoxes->begin(); it != hinput->collisionBoxes->end(); it++)  {
            if (hinput->spriteCollider->checkCollisionWithOffset(*it, 0.f, 1.f)) {
                colliding = true;
                hinput->spriteCollider->clampToCollider(*it, dojo::GameObject2DCollisionBox::bottom);
                break;
            }
        }
        if (!colliding) {
            hinput->sprite->pos.y ++;
        }
        if (hinput->spriteCollider->getAbsolutePos().y + hinput->spriteCollider->getAbsoluteScale().y > hinput->cameraCollider->getAbsolutePos().y + hinput->cameraCollider->getAbsoluteScale().y) {
            hinput->sprite->pos.y = hinput->cameraCollider->getAbsolutePos().y + hinput->cameraCollider->getAbsoluteScale().y - (hinput->spriteCollider->getAbsoluteScale().y + hinput->spriteCollider->getAbsoluteOffset().y);
        }
    }
    if (hinput->window->KEYS[GLFW_KEY_S]) {
        bool colliding = false;
        for (std::vector<dojo::GameObject2DCollisionBox*>::iterator it = hinput->collisionBoxes->begin(); it != hinput->collisionBoxes->end(); it++)  {
            if (hinput->spriteCollider->checkCollisionWithOffset(*it, 0.f, -1.f)) {
                colliding = true;
                hinput->spriteCollider->clampToCollider(*it, dojo::GameObject2DCollisionBox::top);
                break;
            }
        }
        if (!colliding) {
            hinput->sprite->pos.y --;
        }
        if (hinput->spriteCollider->getAbsolutePos().y < hinput->cameraCollider->getAbsolutePos().y) {
            hinput->sprite->pos.y = hinput->cameraCollider->getAbsolutePos().y - (hinput->spriteCollider->relativeOffset.y * hinput->spriteCollider->objScale->y);
        }
    }
    if (hinput->window->KEYS[GLFW_KEY_F]) {
        hinput->sprite->flip = !(hinput->sprite->flip);
    }
    if (hinput->window->KEYS[GLFW_KEY_ESCAPE]) {
        hinput->window->setKill();
    }
}
