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
    dojo::Camera3D *camera;
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

    player->setScale(5, 5);

    dojo::Camera3D *c = new dojo::Camera3D();

    //dojo::GameObject2DCollisionBox *playerCollider = new dojo::GameObject2DCollisionBox(player);
    dojo::GameObject2DCollisionBox *playerCollider = new dojo::GameObject2DCollisionBox(player, 0.5f, 0.5f, 0.5f, 0.5f);
    dojo::GameObject2DCollisionBox *cameraCollider = new dojo::GameObject2DCollisionBox(c);

    std::vector<dojo::GameObject2DSprite*> *objects = new std::vector<dojo::GameObject2DSprite*>;
    std::vector<dojo::GameObject2DCollisionBox*> *colliders = new std::vector<dojo::GameObject2DCollisionBox*>;
    
    dojo::GameObject2DSprite *initialSprite = new dojo::GameObject2DSprite("texture.png");
    initialSprite->setPos(
            (rand() % 30) - 15,
            (rand() % 30) - 15
            );
    initialSprite->setScale(2, 2);
    dojo::GameObject2DCollisionBox *initialCollider = new dojo::GameObject2DCollisionBox(initialSprite);
    objects->push_back(initialSprite);
    colliders->push_back(initialCollider);


    for (int i = 0; i < 10; i++) {
        dojo::GameObject2DSprite *newObj = new dojo::GameObject2DSprite(initialSprite);
        newObj->setScale(2,2);
    newObj->setPos(
            (rand() % 30) - 15,
            (rand() % 30) - 15
            );
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
        window->render(c, playerCollider);
        for (std::vector<dojo::GameObject2DCollisionBox*>::iterator it = colliders->begin(); it != colliders->end(); it++) {
            window->render(c, *it);
        }
        for (std::vector<dojo::GameObject2DSprite*>::iterator it = objects->begin(); it != objects->end(); it++){
            window->render(c, *it);
        }
        window->render(c, player);
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
            //hinput->sprite->pos.x --;
            hinput->sprite->setPos(
                    hinput->sprite->getPos().x - 1,
                    hinput->sprite->getPos().y
                    );
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
            hinput->sprite->setPos(
                    hinput->sprite->getPos().x + 1,
                    hinput->sprite->getPos().y
                    );
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
            hinput->sprite->setPos(
                    hinput->sprite->getPos().x,
                    hinput->sprite->getPos().y + 1
                    );
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
            hinput->sprite->setPos(
                    hinput->sprite->getPos().x,
                    hinput->sprite->getPos().y - 1
                    );
        }
    }
    if (hinput->window->KEYS[GLFW_KEY_F]) {
        hinput->sprite->flip = !(hinput->sprite->flip);
    }
    if (hinput->window->KEYS[GLFW_KEY_ESCAPE]) {
        hinput->window->setKill();
    }

    std::cout 
        << hinput->sprite->getPos().x << " "
        << hinput->sprite->getPos().y << " "
        << hinput->sprite->getPos().z << " "
    << std::endl;
}
