#include "headers/gameObject2DSprite.hpp"

namespace dojo {

GameObject2DSprite::GameObject2DSprite(std::string spritePath) : GameObject() {
    
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

    Renderable::create2DBuffers(vertexArrayObject, vertexBuffer, elementBuffer,
            vertices, elements);
    shaderProgram = Renderable::createBasicShaderProgram("src/shaders/basicVert.vert", "src/shaders/basicFrag.frag");
    texture = Renderable::loadTextureFromFile(spritePath.c_str());

}

GameObject2DSprite::GameObject2DSprite(unsigned int texture, unsigned int vertexArrayObject, unsigned int shaderProgram) : GameObject() {
    texture = texture;
    vertexArrayObject = vertexArrayObject;
    shaderProgram = shaderProgram;
}

GameObject2DSprite::GameObject2DSprite(GameObject2DSprite* obj) : GameObject() {
    texture = obj->texture;
    shaderProgram = obj->shaderProgram;
    vertexArrayObject = obj->vertexArrayObject;
}

GameObject2DSprite::~GameObject2DSprite() {
    delete vertices;
    delete elements;
}

}
