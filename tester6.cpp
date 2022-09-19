#include "src/gameObjects/headers/gameObject3DTextured.hpp"
#include "src/gameObjects/headers/gameObjectSpotLightSource.hpp"
#include "src/headers/dojo.hpp"
#include "src/headers/renderer.hpp"

using namespace dojo;

int main () {
    FileHandler::shaderPath = "src/shaders/";

    auto window = new Window(100, 100, "menuWindow");
    auto renderer = new Renderer(window);
    auto menuItem = new MenuItem("menu Item", glm::vec4(0.25, 0.7, 0.5, 0.15), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.f, 0.f, 0.f));
    auto menuItem2 = new MenuItem("and another one", glm::vec4(0.25, 0.5, 0.5, 0.15), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.f, 0.f, 0.f));
    auto menuItem3 = new MenuItem("and yet another one but this one has quite a long text ontop of it which means that we might have to use more than one line", glm::vec4(0.25, 0.3, 0.5, 0.15), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.f, 0.f, 0.f));
    auto camera = new Camera3D();
    auto light = new GameObjectSpotLightSource(glm::vec3(0.f,0.f,0.f));
    auto cube = new GameObject3DTextured(GameObject3DTextured::Shape::cube, "texture.png");
    cube->move(0.f, -10.f, 5.f);

    while (window->isAlive()) {
        renderer->clear(window);
        cube->rotate(1.f, glm::vec3(1.f, 1.f, 1.f));

        renderer->render(window, menuItem);
        renderer->render(window, menuItem2);
        renderer->render(window, menuItem3);
        renderer->render(window, camera, cube, light);
    }

    delete window;
    delete menuItem;
    delete cube;
    delete light;


}
