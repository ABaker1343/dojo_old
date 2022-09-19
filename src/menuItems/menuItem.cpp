#include "headers/menuItem.hpp"

namespace dojo {

MenuItem::MenuItem(std::string _content, glm::vec4 _pos, glm::vec3 _backgroundColor, glm::vec3 _textColor){
    screenPos = _pos;
    content = _content;
    backgroundColor = _backgroundColor;

    vertices = new std::vector<float> {
        screenPos.x, screenPos.y, 0.f, 0.f, 0.f,
        screenPos.x, screenPos.y + screenPos.w, 0.f, 0.f, 0.f,
        screenPos.x + screenPos.z, screenPos.y + screenPos.w, 0.f, 0.f, 0.f,
        screenPos.x + screenPos.z, screenPos.y, 0.f, 0.f, 0.f,
    };

    elements = new std::vector<unsigned int> {
        0, 1, 2,
        2, 3, 0
    };

    vertexCount = 3;

    vertexBuffer = Renderable::createVertexBuffer(vertices);
    elementBuffer = Renderable::createElementBuffer(elements);


    /*glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);*/

    Renderable::createTexturedObjectBuffers(vertexArrayObject, vertexBuffer, elementBuffer,
            vertices, elements);

}

MenuItem::~MenuItem() {

}

}
