#include "src/headers/dojo.hpp"

void handleInput(dojo::Window*, dojo::GameObject*, dojo::GameObject2DCollisionBox*);

int main () {

    FileHandler::shaderPath = "src/shaders/";

    auto *window = new dojo::Window(100, 100, "newWIndow");
    auto *renderer = new dojo::Renderer(window);
    auto *square = new dojo::GameObject2DSprite("texture.png", glm::vec3(0.f, 0.f, 0.f), glm::vec3(5.f, 5.f, 1.f));
    auto *camera = new dojo::Camera3D();

    auto *collider = new dojo::GameObject2DCollisionBox(square, 0.5f, 0.5f);

    std::cout << "square pos" << square->getPos().x << " " << square->getPos().y << std::endl;
    std::cout << "collider pos" << collider->getAbsolutePos().x << " " << collider->getAbsolutePos().y << std::endl;

    std::cout << "square scale" << square->getScale().x << " " << square->getScale().y << std::endl;
    std::cout << "collider scale" << collider->getAbsoluteScale().x << " " << collider->getAbsoluteScale().y << std::endl;

    std::cout << "collider offset" << collider->getAbsoluteOffset().x << " " << collider->getAbsoluteOffset().y << std::endl;

    while (window->isAlive()) {
        renderer->clear(window);
        handleInput(window, square, collider);
        renderer->render(window, camera, square);
        renderer->render(window, camera, collider);
    }
}

void handleInput(dojo::Window* window, dojo::GameObject* obj, dojo::GameObject2DCollisionBox *collider) {
    if (window->KEYS[GLFW_KEY_W]) {
        //obj->move(0, 1);
        obj->move(
                obj->getPos().x,
                obj->getPos().y + 1
                );
    std::cout << "obj pos" << obj->getPos().x << " " << obj->getPos().y << std::endl;
    std::cout << "collider pos" << collider->getAbsolutePos().x << " " << collider->getAbsolutePos().y << std::endl;
    }
    if (window->KEYS[GLFW_KEY_S]) {
        //obj->move(0, -1);
        obj->move(
                obj->getPos().x,
                obj->getPos().y - 1
                );
    std::cout << "collider pos" << collider->getAbsolutePos().x << " " << collider->getAbsolutePos().y << std::endl;
    }
    if (window->KEYS[GLFW_KEY_A]) {
        //obj->move(-1, 0);
        obj->move(
                obj->getPos().x - 1,
                obj->getPos().y
                );
    std::cout << "collider pos" << collider->getAbsolutePos().x << " " << collider->getAbsolutePos().y << std::endl;
    }
    if (window->KEYS[GLFW_KEY_D]) {
        //obj->move(1, 0);
        obj->move(
                obj->getPos().x + 1,
                obj->getPos().y
                );
    std::cout << "collider pos" << collider->getAbsolutePos().x << " " << collider->getAbsolutePos().y << std::endl;
    }

    if (window->KEYS[GLFW_KEY_F]) {
        obj->flip = !(obj->flip);
    }




}
