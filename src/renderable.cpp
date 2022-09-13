#include "headers/renderable.hpp"
#include "headers/stb_image.h"

namespace dojo {

void Renderable::createTexturedObjectBuffers(unsigned int &vertexArrayObject, unsigned int &vertexBuffer, unsigned int &elementBuffer,
        std::vector<float> *vertices, std::vector<unsigned int> *elements) {
    
    // create buffers and buffer the data
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &elementBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices->size(), vertices->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elements->size(), elements->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    
}

unsigned int Renderable::createBasicShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath){
    std::string vertShaderCode = fileHandler::readShader(vertexShaderPath);
    std::string fragShaderCode = fileHandler::readShader(fragmentShaderPath);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgram = glCreateProgram();

    const char* vertShaderCode_cstr = vertShaderCode.c_str();
    const char* fragShaderCode_cstr = fragShaderCode.c_str();

    glShaderSource(vertexShader, 1, &vertShaderCode_cstr, NULL);
    glShaderSource(fragmentShader, 1, &fragShaderCode_cstr, NULL);

    int success;
    char info[512];

    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, info);
        std::cout << info << std::endl;
        throw std::runtime_error("failed to compile vertex shader");
    }

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, info);
        std::cout << info << std::endl;
        throw std::runtime_error("failed to compile fragment shader");
    }

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, info);
        std::cout << info << std::endl;
        throw std::runtime_error("failed to link shader program");
    }

    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader); 
    //free((char*)vertShaderCode_cstr);
    //free((char*)fragShaderCode_cstr);

    return shaderProgram;

}

unsigned int Renderable::loadTextureFromFile(const char* filepath) {
    // load the texture from a file and return the texture object

    int width, height, numChannels;
    unsigned char* imageData = fileHandler::loadImage(filepath, width, height, numChannels);
    //std::cout << width << " " << height << std::endl;

    if (!imageData) {
        throw std::runtime_error("failed to load texture");
    }

    unsigned int newTexture;
    glGenTextures(1, &newTexture);

    glBindTexture(GL_TEXTURE_2D, newTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    free(imageData);
    return newTexture;

}

unsigned int Renderable::createVertexBuffer(std::vector<float> *vertices) {
    glBindVertexArray(0);
    unsigned int newBuffer;
    glGenBuffers(1, &newBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, newBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices->size(), vertices->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return newBuffer;
}

int Renderable::numElements() {
    return elements->size();
}

}
