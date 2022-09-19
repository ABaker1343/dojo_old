#include "headers/menuItem.hpp"

namespace dojo {

MenuItem::MenuItem(std::string _content, glm::vec4 _pos, glm::vec3 _backgroundColor, glm::vec3 _textColor){
    screenPos = _pos;
    content = _content;
    backgroundColor = _backgroundColor;
    textColor = _textColor;
    texture = 0;

    //vertexBuffer = Renderable::createVertexBuffer(vertices);
    //elementBuffer = Renderable::createElementBuffer(elements);

    vertices = new std::vector<float> {
        screenPos.x, screenPos.y, 0.f, 0.f,
        screenPos.x, screenPos.y + screenPos.w, 0.f, 1.f,
        screenPos.x + screenPos.z, screenPos.y + screenPos.w, 1.f, 1.f,
        screenPos.x + screenPos.z, screenPos.y + screenPos.w, 1.f, 1.f,
        screenPos.x + screenPos.z, screenPos.y, 1.f, 0.f,
        screenPos.x, screenPos.y, 0.f, 0.f,
    };

    vertexCount = vertices->size() / 4;
    
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices->size(), vertices->data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)2);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);


    //Renderable::createTexturedObjectBuffers(vertexArrayObject, vertexBuffer, elementBuffer,
            //vertices, elements);

}

MenuItem::MenuItem(unsigned int _texture, glm::vec4 _pos) {
    screenPos = _pos;
    texture = _texture;

    vertices = new std::vector<float> {
        screenPos.x, screenPos.y, 0.f, 0.f,
        screenPos.x, screenPos.y + screenPos.w, 0.f, 1.f,
        screenPos.x + screenPos.z, screenPos.y + screenPos.w, 1.f, 1.f,
        screenPos.x + screenPos.z, screenPos.y + screenPos.w, 1.f, 1.f,
        screenPos.x + screenPos.z, screenPos.y, 1.f, 0.f,
        screenPos.x, screenPos.y, 0.f, 0.f,
    };

    vertexCount = vertices->size() / 4;

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices->size(), vertices->data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)2);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    //Renderable::createTexturedObjectBuffers(vertexArrayObject, vertexBuffer, elementBuffer, vertices, elements);
}

MenuItem::~MenuItem() {

}
}
