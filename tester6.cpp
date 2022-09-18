#include "src/gameObjects/headers/gameObject3DTextured.hpp"
#include "src/gameObjects/headers/gameObjectSpotLightSource.hpp"
#include "src/headers/dojo.hpp"

using namespace dojo;

int main () {
    FileHandler::shaderPath = "src/shaders/";

    auto window = new Window(100, 100, "menuWindow");
    auto menuItem = new MenuItem(glm::vec4(0.25f, 0.5f, 0.5f, 0.25f), glm::vec3(0.5, 0.5, 0.5), "niceone");
    auto camera = new Camera3D();
    auto light = new GameObjectSpotLightSource(glm::vec3(0.f,0.f,0.f));
    auto cube = new GameObject3DTextured(GameObject3DTextured::Shape::cube, "texture.png");

    while (window->isAlive()) {
        window->clear();
        window->render(menuItem);
        window->render(camera, cube, light);
    }

    delete window;
    delete menuItem;
    delete cube;
    delete light;


}
