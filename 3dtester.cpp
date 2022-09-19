#include "src/headers/dojo.hpp"
#include "src/headers/renderer.hpp"

void handleInputs(dojo::Window*, dojo::Camera3D*, dojo::GameObject*);

int main () {

    FileHandler::shaderPath = "src/shaders/";

    auto *window = new dojo::Window(100, 100, "new Window");
    auto *renderer = new dojo::Renderer(window);
    auto *cube = new dojo::GameObject3DTextured(dojo::GameObject3DTextured::Shape::cube, "texture.png");
    auto *otherObj = new dojo::GameObject3DTextured("monkey.obj", "texture.png",
            glm::vec3(3.f,3.f,0.f));

    auto *lightSource = new dojo::GameObjectSpotLightSource(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f),
            glm::vec3(7.f, 7.f, -5.f));

    auto largeCube = new dojo::GameObject3DTextured(dojo::GameObject3DTextured::Shape::cube, "animation0.jpg",
            glm::vec3(0.f, -5.f, 0.f), glm::vec3(100.f, 1.f, 100.f));
    
    unsigned int texture = renderer->renderTextToTexture("INGERLAND" , 100, 100);
    largeCube->texture = texture;

    auto *camera = new dojo::Camera3D();

    std::vector<dojo::GameObject3DTextured*> *objects = new std::vector<dojo::GameObject3DTextured*>();
    objects->push_back(otherObj);

    for (int i = -10; i < 10; i+= 2) {
        if (i != 0){
            auto newObj = new dojo::GameObject3DTextured(otherObj, glm::vec3(i*2, 0.f, 0.f));
            objects->push_back(newObj);
        }
    }

    while (window->isAlive()) {
        renderer->clear(window);
        renderer->clearShadow();
        //rotate the cube
        cube->rotate(0.5f, glm::vec3(1.f, 1.f, 1.f));
        handleInputs(window, camera, lightSource);
        renderer->renderShadows(cube, lightSource);
        renderer->renderShadows(largeCube, lightSource);
        for (auto obj : *objects) {
            obj->rotate(0.5f, glm::vec3(1.f, 1.f, 1.f));
            renderer->renderShadows(obj, lightSource);
        }
        renderer->render(window, camera, cube, lightSource, 0.7);
        renderer->render(window, camera, lightSource);
        renderer->render(window, camera, largeCube, lightSource);
        for (auto obj : *objects) {
            renderer->render(window, camera, obj, lightSource);
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
