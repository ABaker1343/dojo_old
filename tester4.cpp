#include "src/headers/camera3D.hpp"
#include "src/headers/dojo.hpp"
#include "src/headers/gameObject3DTextured.hpp"
#include "src/headers/gameObjectSpotLightSource.hpp"
#include "src/headers/window.hpp"
#include <GLFW/glfw3.h>

void handleInputs(dojo::Window*, dojo::Camera3D*, dojo::GameObjectSpotLightSource*);

int main () {
    FileHandler::shaderPath = "src/shaders/";

    auto *window = new dojo::Window(100, 100, "newWindow");
    auto *object = new dojo::GameObject3DTextured("monkey.obj", "texture.png",
            glm::vec3(2.f, 0.f, 2.f));
    auto *camera1 = new dojo::Camera3D(0.f, 0.f, 0.5f, 0.5f);
    auto *camera2 = new dojo::Camera3D(0.5f, 0.5f, 0.5f, 0.5f);
    auto *camera3 = new dojo::Camera3D();
    //auto *light = new dojo::GameObjectSpotLightSource(glm::vec3(2.f, 0.f, 2.f));
    auto *light = new dojo::GameObjectSpotLightSource(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f),
            glm::vec3(7.f, 7.f, -5.f));
    auto floor = new dojo::GameObject3DTextured(dojo::GameObject3DTextured::Shape::cube, "texture.png",
            glm::vec3(0.f, -6.f, 0.f), glm::vec3(100.f, 1.f, 100.f));

    while (window->isAlive()) {
        window->clear();
        window->clearShadow();
        handleInputs(window, camera2, light);

        window->renderShadows(object, light);
        window->renderShadows(floor, light);

        window->render(camera2, floor, light);
        window->render(camera2, object, light);

        window->render(camera1, object, light);
        window->render(camera1, floor, light);
        window->render(camera1, light);
        
        //window->render(camera3, object, light);
        //window->render(camera3, floor, light);
        //window->render(camera3, light);
    }

    delete window;
    delete object;
    delete camera1;
    delete camera2;
    delete camera3;
    delete light;
    delete floor;

}

void handleInputs(dojo::Window* win, dojo::Camera3D* cam, dojo::GameObjectSpotLightSource* light) {
    if (win->KEYS[GLFW_KEY_W]){
        cam->move(
                cam->getPos().x,
                cam->getPos().y,
                cam->getPos().z - 1
                );
    }
    if (win->KEYS[GLFW_KEY_S]){
        cam->move(
                cam->getPos().x,
                cam->getPos().y,
                cam->getPos().z + 1
                );
    }
    if (win->KEYS[GLFW_KEY_A]){
        cam->move(
                cam->getPos().x - 1,
                cam->getPos().y,
                cam->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_D]){
        cam->move(
                cam->getPos().x + 1,
                cam->getPos().y,
                cam->getPos().z
                );
    }


    if (win->KEYS[GLFW_KEY_LEFT]){
        light->move(
                light->getPos().x - 1,
                light->getPos().y,
                light->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_RIGHT]){
        light->move(
                light->getPos().x + 1,
                light->getPos().y,
                light->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_UP]){
        light->move(
                light->getPos().x,
                light->getPos().y,
                light->getPos().z - 1
                );
    }
    if (win->KEYS[GLFW_KEY_DOWN]){
        light->move(
                light->getPos().x,
                light->getPos().y,
                light->getPos().z + 1
                );
    }
}
