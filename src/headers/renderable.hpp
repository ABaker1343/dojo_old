#ifndef __HEADER_RENDERABLE
#define __HEADER_RENDERABLE

#include <vector>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "fileHandler.hpp"

namespace dojo {
class Renderable {
    public:
        unsigned int vertexArrayObject;
        unsigned int vertexBuffer;
        unsigned int elementBuffer;

        unsigned int shaderProgram;

        int flip;

        int numElements();

        static void create2DBuffers(unsigned int &vertexArrayObject, unsigned int &vertexBuffer, unsigned int &elementBuffer,
                std::vector<float> *vertices, std::vector<unsigned int> *elements);
        unsigned int createVertexBuffer(std::vector<float> *vertices);
        static unsigned int createBasicShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
        static unsigned int loadTextureFromFile(const char* filepath);

    protected:
        std::vector<float> *vertices;
        std::vector<unsigned int> *elements;
};
}

#endif
