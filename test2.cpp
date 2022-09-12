#include "src/headers/camera3D.hpp"
#include "src/headers/dojo.hpp"
#include "src/headers/gameObject2DCollisionBox.hpp"
#include "src/headers/window.hpp"

void handleInput(dojo::Window*, dojo::GameObject*, dojo::GameObject2DCollisionBox*);

int main () {
    auto *window = new dojo::Window(100, 100, "newWIndow");
    auto *square = new dojo::GameObject2DSprite("texture.png");
    auto *camera = new dojo::Camera3D();

    square->setScale(5.f, 5.f);
    auto *collider = new dojo::GameObject2DCollisionBox(square, 0.5f, 0.5f);

    std::cout << "square pos" << square->getPos().x << " " << square->getPos().y << std::endl;
    std::cout << "collider pos" << collider->getAbsolutePos().x << " " << collider->getAbsolutePos().y << std::endl;

    std::cout << "square scale" << square->getScale().x << " " << square->getScale().y << std::endl;
    std::cout << "collider scale" << collider->getAbsoluteScale().x << " " << collider->getAbsoluteScale().y << std::endl;

    std::cout << "collider offset" << collider->getAbsoluteOffset().x << " " << collider->getAbsoluteOffset().y << std::endl;

    while (window->isAlive()) {
        window->clear();
        handleInput(window, square, collider);
        window->render(camera, collider);
        window->render(camera, square);
    }
}

void handleInput(dojo::Window* window, dojo::GameObject* obj, dojo::GameObject2DCollisionBox *collider) {
    if (window->KEYS[GLFW_KEY_W]) {
        obj->setPos(
                obj->getPos().x,
                obj->getPos().y + 1
                );
    std::cout << "obj pos" << obj->getPos().x << " " << obj->getPos().y << std::endl;
    std::cout << "collider pos" << collider->getAbsolutePos().x << " " << collider->getAbsolutePos().y << std::endl;
    }
    if (window->KEYS[GLFW_KEY_S]) {
        obj->setPos(
                obj->getPos().x,
                obj->getPos().y - 1
                );
    std::cout << "obj pos" << obj->getPos().x << " " << obj->getPos().y << std::endl;
    std::cout << "collider pos" << collider->getAbsolutePos().x << " " << collider->getAbsolutePos().y << std::endl;
    }
    if (window->KEYS[GLFW_KEY_A]) {
        obj->setPos(
                obj->getPos().x -1 ,
                obj->getPos().y
                );
    std::cout << "obj pos" << obj->getPos().x << " " << obj->getPos().y << std::endl;
    std::cout << "collider pos" << collider->getAbsolutePos().x << " " << collider->getAbsolutePos().y << std::endl;
    }
    if (window->KEYS[GLFW_KEY_D]) {
        obj->setPos(
                obj->getPos().x + 1,
                obj->getPos().y
                );
    std::cout << "obj pos" << obj->getPos().x << " " << obj->getPos().y << std::endl;
    std::cout << "collider pos" << collider->getAbsolutePos().x << " " << collider->getAbsolutePos().y << std::endl;
    }
}
