#include "headers/gameObject2DSprite.hpp"

namespace dojo {

GameObject2DSprite::GameObject2DSprite(std::string spritePath, glm::vec3 _pos, glm::vec3 _scale,
        unsigned int _vertexArrayObject, unsigned int _shaderProgram) : GameObject(_pos, _scale) {

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

    if (_vertexArrayObject > 0) {
        this->vertexArrayObject = _vertexArrayObject;
    } else {
        Renderable::createTexturedObjectBuffers(this->vertexArrayObject, this->vertexBuffer, this->elementBuffer,
                this->vertices, this->elements);
    }

    this->texture = Renderable::loadTextureFromFile(spritePath.c_str());

    flip = 0;

    isCopy = false;

}

GameObject2DSprite::GameObject2DSprite(unsigned int _texture, unsigned int _vertexArrayObject, unsigned int _shaderProgram,
        glm::vec3 _pos, glm::vec3 _scale) : GameObject(_pos, _scale) {

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
        Renderable::createTexturedObjectBuffers(this->vertexArrayObject, this->vertexBuffer, this->elementBuffer,
                this->vertices, this->elements);
    }

    this->texture = _texture;

    isCopy = true;
}


GameObject2DSprite::GameObject2DSprite(GameObject2DSprite* obj, glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {
    this->texture = obj->texture;
    this->vertexArrayObject = obj->vertexArrayObject;
    this->vertices = obj->vertices;
    this->elements = obj->elements;
    this->flip = obj->flip;

    isCopy = true;
}

GameObject2DSprite::~GameObject2DSprite() {
    if (!isCopy) {
        delete vertices;
        delete elements;
    }
}

}
