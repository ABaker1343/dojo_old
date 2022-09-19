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

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1000, 1000, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    vertexBuffer = Renderable::createVertexBuffer(vertices);
    elementBuffer = Renderable::createElementBuffer(elements);

    Renderable::createTexturedObjectBuffers(vertexArrayObject, vertexBuffer, elementBuffer,
            vertices, elements);

}

MenuItem::~MenuItem() {

}

void MenuItem::renderTexture() {
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    unsigned int renderBuffer; // this is used because we dont actually want the depth or stencil data and this will not worry about formatting them
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1000, 1000);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH24_STENCIL8, GL_RENDERBUFFER, renderBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("failed to create framebuffer for menu item texture rendering");
    }

    // use the frambuffer to render out the text to a texture


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteRenderbuffers(1, &renderBuffer);


}

}
