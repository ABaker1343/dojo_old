#include "headers/gameObjectGenericTextuedObject.hpp"

namespace dojo {

GameObject3DGenericTexturedObject::GameObject3DGenericTexturedObject(std::string objectPath, std::string texturePath,
        glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {

    std::vector<float> *textureCoords = new std::vector<float>();
    vertices = new std::vector<float>();
    elements = new std::vector<unsigned int>();

    fileHandler::loadModel(objectPath.c_str(), vertices, textureCoords, elements);

    unsigned int textureOffset = vertices->size();

    vertices->insert(vertices->end(), textureCoords->begin(), textureCoords->end());

    Renderable::createTexturedObjectBuffersWithOffsetTextures(vertexArrayObject, vertexBuffer, elementBuffer,
            vertices, textureOffset, elements);
    shaderProgram = Renderable::createBasicShaderProgram("src/shaders/basicVert.vert", "src/basicFrag.frag");
    texture = loadTextureFromFile(texturePath.c_str());

    for (float f : *vertices) {
        std::cout << f << " ";
    } std::cout << std::endl;
    
    delete textureCoords;

}

GameObject3DGenericTexturedObject::~GameObject3DGenericTexturedObject() {
    delete vertices;
    delete elements;
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &elementBuffer);
    glDeleteTextures(1, &texture);
}

}
