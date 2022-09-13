#include "src/headers/camera3D.hpp"
#include "src/headers/dojo.hpp"
#include "src/headers/gameObject3DCube.hpp"
#include "src/headers/gameObject3DTextured.hpp"
#include "src/headers/window.hpp"

void handleInputs(dojo::Window*, dojo::Camera3D*, dojo::GameObject3DTextured*);

int main () {
    auto *window = new dojo::Window(100, 100, "new Window");
    auto *camera = new dojo::Camera3D();
    auto *cube = new dojo::GameObject3DTextured(dojo::GameObject3DTextured::Shape::cube, "texture.png");
    auto *otherObj = new dojo::GameObject3DTextured("monkey.obj", "texture.png",
            glm::vec3(3.f,3.f,0.f), glm::vec3(10.f, 10.f, 10.f));

    while (window->isAlive()) {
        window->clear();
        //rotate the cube
        cube->rotate(0.5f, glm::vec3(1.f, 1.f, 1.f));
        handleInputs(window, camera, cube);
        window->render(camera, cube);
        window->render(camera, otherObj);
    }

    delete window;
    delete camera;
    delete cube;
    delete otherObj;
}

void handleInputs(dojo::Window* win, dojo::Camera3D* cam, dojo::GameObject3DTextured* cube) {
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
    if (win->KEYS[GLFW_KEY_F]) {
        cube->scale(1.1, 1.1, 1.1);
    }

}
