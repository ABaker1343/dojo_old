#include "src/headers/dojo.hpp"
#include "src/headers/renderer.hpp"

void handleInputs(dojo::Window*, dojo::Camera3D*, dojo::GameObjectPointLightSource*);

int main () {

    srand(time(0));

    FileHandler::shaderPath = "src/shaders/";

    auto *window = new dojo::Window(100, 100, "newWindow");
    auto *renderer = new dojo::Renderer(window);
    auto *object = new dojo::GameObject3DTextured("monkey.obj", "texture.png",
            glm::vec3(2.f, 0.f, 2.f));
    auto *light = new dojo::GameObjectPointLightSource();
    //auto *light = new dojo::GameObjectSpotLightSource(glm::vec3(0.f, 0.f, 0.f));
    auto floor = new dojo::GameObject3DTextured(dojo::GameObject3DTextured::Shape::cube, "texture.png",
            glm::vec3(0.f, -6.f, 0.f), glm::vec3(100.f, 1.f, 100.f));
    auto *backwall = new dojo::GameObject3DTextured(dojo::GameObject3DTextured::Shape::cube, "texture.png",
            glm::vec3(0.f, 44.f, -50.f), glm::vec3(100.f, 100.f, 1.f));
    auto *camera3 = new dojo::Camera3D(object->getPos());


    std::vector<dojo::GameObject3DTextured> *objects = new std::vector<dojo::GameObject3DTextured>();
    objects->push_back(object);

    for (int i = 0; i < 500; i++) {
        auto newObj = dojo::GameObject3DTextured(object, 
                    glm::vec3(
                        (rand() % 51) - 25,
                        (rand() % 26),
                        (rand() % 51) - 25
                        ));

        float x = (float)(rand() % 10) / 100;
        float y = (float)(rand() % 10) / 100;
        float z = (float)(rand() % 10) / 100;
        newObj.rotate((float)(rand() % 90), glm::vec3(x, y, z));
        objects->push_back(newObj);
    }

    window->hidePointer();

    while (window->isAlive()) {
        renderer->clear(window);
        renderer->clearShadow();
        handleInputs(window, camera3, light);

        for (auto& o : *objects){
            o.rotate(0.5f, glm::vec3(1.0f, 1.f, 1.f));

            renderer->renderShadows(&o, light);
        }

        renderer->renderShadows(floor, light);
        renderer->renderShadows(backwall, light);

        for (auto& o : *objects){
            renderer->render(window, camera3, &o, light);
        }
        
        //window->render(camera3, object, light);
        renderer->render(window, camera3, floor, light);
        renderer->render(window, camera3, backwall, light);
        renderer->render(window, camera3, light);
    }

    delete window;
    delete object;
    delete camera3;
    delete light;
    delete floor;

}

void handleInputs(dojo::Window* win, dojo::Camera3D* cam, dojo::GameObjectPointLightSource* light) {

    static double prevMousePosx = win->MOUSE_POSITION_X;
    static double prevMousePosy = win->MOUSE_POSITION_Y;
    static double mouseMovementx;
    static double mouseMovementy;

    mouseMovementx = win->MOUSE_POSITION_X - prevMousePosx;
    prevMousePosx = win->MOUSE_POSITION_X;
    mouseMovementy = win->MOUSE_POSITION_Y - prevMousePosy;
    prevMousePosy = win->MOUSE_POSITION_Y;

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
    if (win->KEYS[GLFW_KEY_N]){
        cam->move(
                cam->getPos().x,
                cam->getPos().y - 1,
                cam->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_M]){
        cam->move(
                cam->getPos().x,
                cam->getPos().y + 1,
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
    if (win->KEYS[GLFW_KEY_J]){
        light->move(
                light->getPos().x,
                light->getPos().y - 1,
                light->getPos().z
                );
    }
    if (win->KEYS[GLFW_KEY_K]){
        light->move(
                light->getPos().x,
                light->getPos().y + 1,
                light->getPos().z
                );
    }


    // mouse movement

    if (mouseMovementx > 0 || mouseMovementx < 0) {
        cam->rotate(-mouseMovementx, glm::vec3(0.f, 1.f, 0.f));
    }
    if (mouseMovementy > 0 || mouseMovementy < 0) {
        cam->rotate(-mouseMovementy, glm::vec3(1.f, 0.f, 0.f));
    }

}
