#include <iostream>
#include <chrono>
#include <thread>

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
} HANDLER_INPUT;

void handleInputs(HANDLER_INPUT*);

int main () {

    dojo::Window *window = new dojo::Window(500, 500, "dojoWindow");

    //dojo::GameObject2DSprite *player = new dojo::GameObject2DSprite("bgCatAndSakura.jpg");
    dojo::GameObject2DAnimatedSprite *player = new dojo::GameObject2DAnimatedSprite(4, "animation0.jpg");
    player->addAnimation("walking", 4, "makima.jpg");
    player->scale.x = 20; player->scale.y = 20;

    dojo::Camera2D *c = new dojo::Camera2D();

    dojo::GameObject2DCollisionBox *playerCollider = new dojo::GameObject2DCollisionBox(player);
    dojo::GameObject2DCollisionBox *cameraCollider = new dojo::GameObject2DCollisionBox(c);

    HANDLER_INPUT hinputs;
    hinputs.sprite = player;
    hinputs.cameraCollider = cameraCollider;
    hinputs.spriteCollider = playerCollider;
    hinputs.window = window;
    hinputs.camera = c;

    std::chrono::duration<double> frametime = std::chrono::milliseconds(50);

    while (window->isAlive()) {
        auto start = std::chrono::system_clock::now();

        handleInputs(&hinputs);
        window->clear();
        window->render2D(c, player);
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

    return 0;
}

void handleInputs(HANDLER_INPUT *hinput) {
    if (hinput->window->KEYS[GLFW_KEY_A]) {
        if (hinput->spriteCollider->checkCollision(hinput->cameraCollider))
            hinput->sprite->pos.x --;
        else
            hinput->sprite->pos.x = hinput->camera->pos.x;
        std::cout << hinput->sprite->pos.x << " ," << hinput->sprite->pos.y << std::endl;
    }
    if (hinput->window->KEYS[GLFW_KEY_D]) {
        if (hinput->spriteCollider->checkCollision(hinput->cameraCollider))
            hinput->sprite->pos.x ++;
        else
            hinput->sprite->pos.x = hinput->camera->pos.x + hinput->camera->scale.x - hinput->sprite->scale.x;
        std::cout << hinput->sprite->pos.x << " ," << hinput->sprite->pos.y << std::endl;
    }
   if (hinput->window->KEYS[GLFW_KEY_S]) {
        if (hinput->spriteCollider->checkCollision(hinput->cameraCollider))
            hinput->sprite->pos.y --;
        else
            hinput->sprite->pos.y = hinput->camera->pos.y;
        std::cout << hinput->sprite->pos.x << " ," << hinput->sprite->pos.y << std::endl;
    }
    if (hinput->window->KEYS[GLFW_KEY_W]) {
        if (hinput->spriteCollider->checkCollision(hinput->cameraCollider))
            hinput->sprite->pos.y ++;
        else
            hinput->sprite->pos.y = hinput->camera->pos.y + hinput->camera->scale.y - hinput->sprite->scale.y;
        std::cout << hinput->sprite->pos.x << " ," << hinput->sprite->pos.y << std::endl;
    }
    if (hinput->window->KEYS[GLFW_KEY_F]) {
        hinput->sprite->flip = !(hinput->sprite->flip);
    }
}
