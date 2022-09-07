#include <iostream>

#include "src/headers/camera2D.hpp"
#include "src/headers/dojo.hpp"
#include "src/headers/gameObject2DSprite.hpp"
#include "src/headers/window.hpp"


void handleInputs(dojo::Window*, dojo::GameObject2DSprite*);

int main () {

    dojo::Window *window = new dojo::Window(500, 500, "dojoWindow");
    dojo::GameObject2DSprite *player = new dojo::GameObject2DSprite("bgCatAndSakura.jpg");
    dojo::Camera2D *c = new dojo::Camera2D();
    
    while (window->isAlive()) {
        handleInputs(window, player);
        window->clear();
        window->render2D(c, player);
    }

    delete window;
    delete player;
    delete c;

    return 0;
}

void handleInputs(dojo::Window *w, dojo::GameObject2DSprite *s) {
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
        std::cout << "pos: " << s->pos.x << ", " << s->pos.y << ", " << s->pos.z 
            << " | scale: " << s->scale.x << ", " << s->scale.y << ", " << s->scale.z << std::endl;
}
