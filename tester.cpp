#include <iostream>
#include <chrono>
#include <thread>

#include "src/headers/camera2D.hpp"
#include "src/headers/dojo.hpp"
#include "src/headers/gameObject2DAnimatedSprite.hpp"
#include "src/headers/gameObject.hpp"
#include "src/headers/gameObject2DSprite.hpp"
#include "src/headers/window.hpp"


void handleInputs(dojo::Window*, dojo::GameObject2DAnimatedSprite*);

int main () {

    dojo::Window *window = new dojo::Window(500, 500, "dojoWindow");

    //dojo::GameObject2DSprite *player = new dojo::GameObject2DSprite("bgCatAndSakura.jpg");
    dojo::GameObject2DAnimatedSprite *player = new dojo::GameObject2DAnimatedSprite(4, "animation0.jpg");
    player->addAnimation("walking", 4, "makima.jpg");
    player->scale.x = 20; player->scale.y = 20;

    dojo::Camera2D *c = new dojo::Camera2D();


    std::chrono::duration<double> frametime = std::chrono::milliseconds(50);

    while (window->isAlive()) {
        auto start = std::chrono::system_clock::now();

        handleInputs(window, player);
        window->clear();
        window->render2D(c, player);
        if (!player->nextFrame()) {
            if (player->currentAnimationName() == "default") {
                player->setCurrentAnimation("walking");
            } else {
                player->setCurrentAnimation("default");
            }
        }
        std::cout << player->currentFrame() << std::endl;

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

void handleInputs(dojo::Window *w, dojo::GameObject2DAnimatedSprite *s) {
    if (w->KEYS[GLFW_KEY_A]) {
        s->pos.x --;
    }
    if (w->KEYS[GLFW_KEY_D]) {
        s->pos.x ++;
    }
    if (w->KEYS[GLFW_KEY_S]) {
        s->pos.y --;
    }
    if (w->KEYS[GLFW_KEY_W]) {
        s->pos.y ++;
    }
    if (w->KEYS[GLFW_KEY_F]) {
        s->flip = !(s->flip);
    }
        std::cout << "pos: " << s->pos.x << ", " << s->pos.y << ", " << s->pos.z 
            << " | scale: " << s->scale.x << ", " << s->scale.y << ", " << s->scale.z << std::endl;
}
