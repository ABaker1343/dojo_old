#include "headers/gameObjectPointLightSource.hpp"

namespace dojo {

    GameObjectPointLightSource::GameObjectPointLightSource(glm::vec3 color, glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {
        // right, left, top, bottom, near and far. 
        /*lightViewTransforms = new std::vector<glm::mat4> {
            glm::lookAt(pos, pos + glm::vec3(1.0f, 0.0f, 0.f), glm::vec3(0.f, 1.f, 0.f)), // looking right
            glm::lookAt(pos, pos + glm::vec3(-1.0f, 0.0f, 0.f), glm::vec3(0.f, 1.f, 0.f)), // looking left
            glm::lookAt(pos, pos + glm::vec3(0.0f, 1.0f, 0.f), glm::vec3(0.f, 0.f, 1.f)), // looking up
            glm::lookAt(pos, pos + glm::vec3(0.0f, -1.0f, 0.f), glm::vec3(0.f, 0.f, -1.f)), // looking down
            glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, 1.f), glm::vec3(0.f, 1.f, 0.f)), // looking backward
            glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, -1.f), glm::vec3(0.f, 1.f, 0.f)), // looking forward
        };*/

        
        lightViewTransforms = new std::vector<glm::mat4> {
                 glm::lookAt(pos, pos + glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)),
                 glm::lookAt(pos, pos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)),
                 glm::lookAt(pos, pos + glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)),
                 glm::lookAt(pos, pos + glm::vec3( 0.0,-1.0, 0.0), glm::vec3(0.0, 0.0,-1.0)),
                 glm::lookAt(pos, pos + glm::vec3( 0.0, 0.0, 1.0), glm::vec3(0.0,-1.0, 0.0)),
                 glm::lookAt(pos, pos + glm::vec3( 0.0, 0.0,-1.0), glm::vec3(0.0,-1.0, 0.0))
                 };


        nearPlane = 1.f;
        farPlane = 50.f;

        lightProjectionTransform = glm::perspective(glm::radians(90.f), 1600.f/900.f, nearPlane, farPlane);

        lightColor = color;
    }

    GameObjectPointLightSource::~GameObjectPointLightSource() {
        delete lightViewTransforms;
    }

    std::vector<glm::mat4> GameObjectPointLightSource::getViewTransforms() {
        glm::vec3 pos = getPos();
        //delete lightViewTransforms;
        lightViewTransforms = new std::vector<glm::mat4> {
                 glm::lookAt(pos, pos + glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)),
                 glm::lookAt(pos, pos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)),
                 glm::lookAt(pos, pos + glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)),
                 glm::lookAt(pos, pos + glm::vec3( 0.0,-1.0, 0.0), glm::vec3(0.0, 0.0,-1.0)),
                 glm::lookAt(pos, pos + glm::vec3( 0.0, 0.0, 1.0), glm::vec3(0.0,-1.0, 0.0)),
                 glm::lookAt(pos, pos + glm::vec3( 0.0, 0.0,-1.0), glm::vec3(0.0,-1.0, 0.0))
                 };
        return *lightViewTransforms;
    }

    glm::mat4 GameObjectPointLightSource::getProjectionTransform() {
        return lightProjectionTransform;
    }



}
