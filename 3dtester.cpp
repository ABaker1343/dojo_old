#include "src/headers/camera3D.hpp"
#include "src/headers/dojo.hpp"
#include "src/headers/gameObject3DTextured.hpp"
#include "src/headers/gameObjectLightSource.hpp"
#include "src/headers/window.hpp"

void handleInputs(dojo::Window*, dojo::Camera3D*, dojo::GameObject*);

int main () {
    auto *window = new dojo::Window(100, 100, "new Window");
    auto *camera = new dojo::Camera3D();
    auto *cube = new dojo::GameObject3DTextured(dojo::GameObject3DTextured::Shape::cube, "texture.png");
    auto *otherObj = new dojo::GameObject3DTextured("monkey.obj", "texture.png",
            glm::vec3(3.f,3.f,0.f));

    auto *lightSource = new dojo::GameObjectLightSource(glm::vec3(0.8f, 0.3f, 0.2f));

    std::vector<dojo::GameObject3DTextured*> *objects = new std::vector<dojo::GameObject3DTextured*>();
    objects->push_back(otherObj);

    for (int i = -10; i < 10; i+= 2) {
        auto newObj = new dojo::GameObject3DTextured(otherObj, glm::vec3(i*2, 0.f, 0.f));
        objects->push_back(newObj);
    }

    while (window->isAlive()) {
        window->clear();
        //rotate the cube
        cube->rotate(0.5f, glm::vec3(1.f, 1.f, 1.f));
        handleInputs(window, camera, lightSource);
        //window->render(camera, cube, lightSource);
        window->render(camera, lightSource);
        for (auto obj : *objects) {
            //obj->rotate(0.5f, glm::vec3(1.f, 1.f, 1.f));
            window->render(camera, obj, lightSource);
        }
    }

    delete window;
    delete camera;
    delete cube;
    
    for (auto obj : *objects){
        delete obj;
    }
    delete objects;
}

void handleInputs(dojo::Window* win, dojo::Camera3D* cam, dojo::GameObject* cube) {
    if (win->KEYS[GLFW_KEY_S]) {
        //cube->move(0,0,-0.5f);
        cube->move(
                cube->getPos().x,
                cube->getPos().y,
                cube->getPos().z + 0.5f
                );
    }
    if (win->KEYS[GLFW_KEY_W]) {
        //cube->move(0,0,0.5f);
        cube->move(
                cube->getPos().x,
                cube->getPos().y,
                cube->getPos().z + -0.5f
                );
    }
    if (win->KEYS[GLFW_KEY_D]) {
        //cube->move(0.5f, 0, 0);
        cube->move(
                cube->getPos().x + 0.5f,
                cube->getPos().y,
                cube->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_A]) {
        //cube->move(-0.5f, 0, 0);
        cube->move(
                cube->getPos().x + -0.5f,
                cube->getPos().y,
                cube->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_R]) {
        //cube->move(-0.5f, 0, 0);
        cube->move(
                cube->getPos().x,
                cube->getPos().y + 0.5f,
                cube->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_T]) {
        //cube->move(-0.5f, 0, 0);
        cube->move(
                cube->getPos().x,
                cube->getPos().y - 0.5f,
                cube->getPos().z
                );
    }

    if (win->KEYS[GLFW_KEY_RIGHT]) {
        cam->move(
                cam->getPos().x + 0.1f,
                cam->getPos().y,
                cam->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_LEFT]) {
        cam->move(
                cam->getPos().x - 0.1,
                cam->getPos().y,
                cam->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_UP]) {
        cam->move(
                cam->getPos().x,
                cam->getPos().y + 0.1,
                cam->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_DOWN]) {
        cam->move(
                cam->getPos().x,
                cam->getPos().y - 0.1,
                cam->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_N]) {
        cam->move(
                cam->getPos().x,
                cam->getPos().y,
                cam->getPos().z - 1
                );
    }
    if (win->KEYS[GLFW_KEY_M]) {
        cam->move(
                cam->getPos().x,
                cam->getPos().y,
                cam->getPos().z + 1
                );
    }

    if (win->KEYS[GLFW_KEY_F]) {
        cube->scale(1.1, 1.1, 1.1);
    }
    if (win->KEYS[GLFW_KEY_G]) {
        cube->scale(0.9, 0.9, 0.9);
    }

}
