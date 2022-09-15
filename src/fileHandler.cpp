#include <glm/geometric.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "headers/stb_image.h"
#include "headers/fileHandler.hpp"

namespace fileHandler {
    std::string readShader(std::string filepath) {
        std::ifstream stream(filepath);
        std::stringstream buffer;
        buffer << stream.rdbuf();
        return buffer.str() + '\0';
    }

void loadModel(const char* filepath, std::vector<float> *vertices, std::vector<float> *textureCoords, std::vector<float> *vertexNormals, std::vector<unsigned int> *elements) {

    std::ifstream file(filepath);

    std::vector<float> *tempTextures = new std::vector<float>();
    std::vector<unsigned int> *textureElems = new std::vector<unsigned int>();

    std::vector<float> *tempNormals = new std::vector<float>();
    std::vector<unsigned int> *normalElems = new std::vector<unsigned int>();
    
    std::vector<float> *tempVertices = new std::vector<float>();
    std::vector<unsigned int> *vertexElems = new std::vector<unsigned int>();

    if (!file.is_open()) {
        throw std::runtime_error("failed to open model file");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string identifier;

        if (!(iss >> identifier)) {
            continue;
        }

        if (identifier.compare("v") == 0) {
            float first, second, third;
            iss >> first >> second >> third;
            tempVertices->push_back(first);
            tempVertices->push_back(second);
            tempVertices->push_back(third);
        } else if (identifier.compare("vt") == 0) {
            float first, second;
            iss >> first >> second;
            tempTextures->push_back(first);
            tempTextures->push_back(second);
        } else if (identifier.compare("vn") == 0) {
            float first, second, third;
            iss >> first >> second >> third;
            tempNormals->push_back(first);
            tempNormals->push_back(second);
            tempNormals->push_back(third);
        } else if (identifier.compare("f") == 0) {
            std::string first, second, third, fourth, tempString;
            unsigned int temp;
            unsigned int textureElem = 0;
            unsigned int normalElem = 0;
            iss >> first >> second >> third;

            int pos = first.find("/");
            tempString = first.substr(0, pos);
            temp = stoi(tempString);
            elements->push_back(temp-1);
            first = first.erase(0,pos + 1);
            pos = first.find("/");
            tempString = first.substr(0, pos);
            textureElem = std::stoi(tempString);
            textureElems->push_back(textureElem -1);
            first = first.erase(0, pos + 1);
            tempString = first;
            normalElem = std::stoi(tempString);
            normalElems->push_back(normalElem - 1);

            pos = second.find("/");
            tempString = second.substr(0, pos);
            temp = stoi(tempString);
            elements->push_back(temp-1);
            second.erase(0,pos + 1);
            pos = second.find("/");
            tempString = second.substr(0, pos);
            textureElem = std::stoi(tempString);
            textureElems->push_back(textureElem -1);
            second = second.erase(0, pos + 1);
            tempString = second;
            normalElem = std::stoi(tempString);
            normalElems->push_back(normalElem - 1);

            pos = third.find("/");
            tempString = third.substr(0, pos);
            temp = stoi(tempString);
            elements->push_back(temp-1);
            third.erase(0,pos + 1);
            pos = third.find("/");
            tempString = third.substr(0, pos);
            textureElem = std::stoi(tempString);
            textureElems->push_back(textureElem -1);
            third = third.erase(0, pos + 1);
            tempString = third;
            normalElem = std::stoi(tempString);
            normalElems->push_back(normalElem - 1);

        }
    }

    //textureCoords->resize(vertices->size());
    //for (auto v : *tempVertices) {
        //vertices->push_back(v);
    //}

    /*(for (int i = 0; i < elements->size(); i++){
        if ((*elements)[i] * 2 >= textureCoords->size()){
            textureCoords->resize((*elements)[i] * 2 + 2);
        }
        (*textureCoords)[(*elements)[i] * 2] = (*tempTextures)[(*textureElems)[i] * 2];
        (*textureCoords)[(*elements)[i] * 2 + 1] = (*tempTextures)[(*textureElems)[i] * 2 + 1];
    }*/

    for (int i = 0; i < elements->size(); i++) {

        float vertexX = (*tempVertices)[ ( ( *elements )[i] * 3) ];
        float vertexY = (*tempVertices)[ ( ( *elements )[i] * 3) + 1 ];
        float vertexZ = (*tempVertices)[ ( ( *elements )[i] * 3) + 2 ];

        float textureX = (*tempTextures)[ ( ( *textureElems )[i] * 2 ) ];
        float textureY = (*tempTextures)[ ( ( *textureElems )[i] * 2 ) + 1 ];

        float normalX = (*tempNormals)[ ( ( *normalElems )[i] * 3 ) ];
        float normalY = (*tempNormals)[ ( ( *normalElems )[i] * 3 ) + 1 ];
        float normalZ = (*tempNormals)[ ( ( *normalElems )[i] * 3 ) + 2 ];
        
        vertices->push_back(vertexX);
        vertices->push_back(vertexY);
        vertices->push_back(vertexZ);
        textureCoords->push_back(textureX);
        textureCoords->push_back(textureY);
        vertexNormals->push_back(normalX);
        vertexNormals->push_back(normalY);
        vertexNormals->push_back(normalZ);
    }

    delete tempTextures;
    delete textureElems;
    delete tempNormals;
    delete normalElems;
    delete tempVertices;
    delete vertexElems;

}

unsigned char* loadImage(const char* filepath, int& width, int& height, int& numChannels) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filepath, &width, &height, &numChannels, 0);

    return data;
}

}
