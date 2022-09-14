#include "headers/gameObject3DTextured.hpp"

namespace dojo {

GameObject3DTextured::GameObject3DTextured(Shape shape, std::string texturePath,
        glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {

    switch (shape) {
        case cube:
            createCubeVertices();
    }

    createTexturedObjectBuffers(vertexArrayObject, vertexBuffer, elementBuffer,
            vertices, elements);
    shaderProgram = createBasicShaderProgram("src/shaders/basicVert.vert", "src/shaders/basicFrag.frag");
    texture = loadTextureFromFile(texturePath.c_str());

    this->isClone = false;
}

void GameObject3DTextured::createCubeVertices() {

    vertices = new std::vector<float> {
        // x, y, z, texX, texY
        // front face
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

        //back face
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    };

    elements = new std::vector<unsigned int> {
        //front face
        0, 1, 2,
        2, 3, 0,
        //back face
        4, 5, 6,
        6, 7, 4,
        //left face
        0, 1, 5,
        5, 4, 0,
        //right face
        3, 2, 6,
        6, 7, 3,
        //top face
        1, 5, 6,
        6, 2, 1,
        //bottom face
        0, 4, 7,
        7, 3, 0
    };

}

GameObject3DTextured::GameObject3DTextured(std::string objectPath, std::string texturePath,
        glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {

    std::vector<float> *textureCoords = new std::vector<float>();
    vertices = new std::vector<float>();
    elements = new std::vector<unsigned int>();

    fileHandler::loadModel(objectPath.c_str(), vertices, textureCoords, elements);

    unsigned int textureOffset = vertices->size();

    vertices->insert(vertices->end(), textureCoords->begin(), textureCoords->end());

    Renderable::createTexturedObjectBuffersWithOffsetTextures(vertexArrayObject, vertexBuffer, elementBuffer,
            vertices, textureOffset, elements);
    shaderProgram = Renderable::createBasicShaderProgram("src/shaders/basicVert.vert", "src/shaders/basicFrag.frag");
    texture = loadTextureFromFile(texturePath.c_str());

    
    delete textureCoords;

    this->isClone = false;

}

GameObject3DTextured::GameObject3DTextured(GameObject3DTextured *obj, glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {
    this->vertexArrayObject = obj->vertexArrayObject;
    this->shaderProgram = obj->shaderProgram;
    this->texture = obj->texture;
    this->elements = obj->elements;
    this->vertices = obj->vertices;

    this->isClone = true;
}

GameObject3DTextured::~GameObject3DTextured() {
    if (!isClone){
        delete vertices;
        delete elements;
        glDeleteVertexArrays(1, &vertexArrayObject);
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &elementBuffer);
        glDeleteTextures(1, &texture);
    }
}

}
