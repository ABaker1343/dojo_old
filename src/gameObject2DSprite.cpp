#include "headers/gameObject2DSprite.hpp"

namespace dojo {

GameObject2DSprite::GameObject2DSprite(std::string spritePath, glm::vec3 pos, glm::vec3 scale,
        unsigned int vertexArrayObject, unsigned int shaderProgram) : GameObject(pos, scale) {
    
    vertices = new std::vector<float> {
        // x, y, z, texture x, texture y
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    };

    elements = new std::vector<unsigned int> {
        0, 1, 2,
        2, 3, 0,
    };

    if (vertexArrayObject > 0) {
        this->vertexArrayObject = vertexArrayObject;
    } else {
        Renderable::create2DBuffers(vertexArrayObject, vertexBuffer, elementBuffer,
            vertices, elements);
    }

    if (shaderProgram > 0) {
        this->shaderProgram = shaderProgram;
    } else {
    shaderProgram = Renderable::createBasicShaderProgram("src/shaders/basicVert.vert", "src/shaders/basicFrag.frag");
    }

    texture = Renderable::loadTextureFromFile(spritePath.c_str());

    flip = 0;

}

GameObject2DSprite::GameObject2DSprite(unsigned int texture, unsigned int vertexArrayObject, unsigned int shaderProgram,
        glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {
    
    vertices = new std::vector<float> {
        // x, y, z, texture x, texture y
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    };

    elements = new std::vector<unsigned int> {
        0, 1, 2,
        2, 3, 0,
    };

    if (vertexArrayObject > 0) {
        this->vertexArrayObject = vertexArrayObject;
    } else {
        Renderable::create2DBuffers(vertexArrayObject, vertexBuffer, elementBuffer,
            vertices, elements);
    }

    if (shaderProgram > 0) {
        this->shaderProgram = shaderProgram;
    } else {
    shaderProgram = Renderable::createBasicShaderProgram("src/shaders/basicVert.vert", "src/shaders/basicFrag.frag");
    }

    this->texture = texture;
}


GameObject2DSprite::GameObject2DSprite(GameObject2DSprite* obj, glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {
    texture = obj->texture;
    shaderProgram = obj->shaderProgram;
    vertexArrayObject = obj->vertexArrayObject;
    elements = obj->elements;
    flip = obj->flip;
}

GameObject2DSprite::~GameObject2DSprite() {
    delete vertices;
    delete elements;
}

}
