#include "headers/gameObject3DCube.hpp"

namespace dojo {

GameObject3DCube::GameObject3DCube(std::string texturePath, glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {
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

    Renderable::createTexturedObjectBuffers(this->vertexArrayObject, this->vertexBuffer, this->elementBuffer,
            this->vertices, this->elements);
    this->shaderProgram = Renderable::createBasicShaderProgram("src/shaders/basicVert.vert", "src/shaders/basicFrag.frag");
    this->texture = loadTextureFromFile(texturePath.c_str());

}

GameObject3DCube::~GameObject3DCube() {
    delete vertices;
    delete elements;
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteTextures(1, &texture);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &elementBuffer);
}

}
