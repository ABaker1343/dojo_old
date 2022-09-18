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
        unsigned int vertexArrayObject = 0;

        int numElements();
        int numVertices();

        static void createTexturedObjectBuffers(unsigned int &vertexArrayObject, unsigned int &vertexBuffer, unsigned int &elementBuffer,
                std::vector<float> *vertices, std::vector<unsigned int> *elements);
        static void createTexturedObjectBuffersWithOffsetTextures(unsigned int &vertexArrayObject, unsigned int &vertexBuffer, unsigned int &elementBuffer,
                std::vector<float> *vertices, unsigned int textureOffset, unsigned int normalsOffset, std::vector<unsigned int> *elements);

        static unsigned int createVertexBuffer(std::vector<float> *vertices);
        static unsigned int createElementBuffer(std::vector<unsigned int> *elements);

        static unsigned int createBasicShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
        static unsigned int createBasicShaderProgramWithGeometry(std::string vertexShaderPath, std::string GeometryShaderPath, std::string fragmentShaderPath);

        static unsigned int loadTextureFromFile(const char* filepath);

    protected:
        unsigned int vertexBuffer = 0;
        unsigned int elementBuffer = 0;

        int vertexCount;
        std::vector<float> *vertices;
        std::vector<unsigned int> *elements;
};
}

#endif
