#define STB_IMAGE_IMPLEMENTATION
#include "headers/stb_image.h"
#include "headers/fileHandler.hpp"

#include <byteswap.h>
#include <fstream>
#include <glm/geometric.hpp>


std::string FileHandler::shaderPath = "shaders/";

std::string FileHandler::readShader(std::string filepath) {
    std::ifstream stream(shaderPath + filepath);
    std::stringstream buffer;
    buffer << stream.rdbuf();
    return buffer.str() + '\0';
}

void FileHandler::loadModel(const char* filepath, std::vector<float> *vertices, std::vector<float> *textureCoords, std::vector<float> *vertexNormals, std::vector<unsigned int> *elements) {

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

    for (unsigned int i = 0; i < elements->size(); i++) {

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

void FileHandler::loadModelFBX(const char* filepath, std::vector<float> *vertices, std::vector<float> *textures, std::vector<float> *normals) {
    // loading fbx binary files
    
    struct ARRAY_TYPE {
        unsigned int arrayLength;
        unsigned int encoding;
        unsigned int compressedLength;
        void* data;
    };

    struct SPECIAL_TYPE {
        unsigned int length;
        char* data;
    };

    struct PROPERTY {
        char typeCode;
        void* data;
    };

    struct NODE {
        unsigned int endOffset;
        unsigned int numProperties;
        unsigned int propertyListLen;
        unsigned char nameLen;
        char* name;
        PROPERTY* properties;
    };
    
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);
    size_t filesize = file.tellg();
    std::vector<char> *buffer = new std::vector<char>(filesize);
    file.seekg(0);
    
    file.read(buffer->data(), filesize);

    file.close();
    
    unsigned long filemark = 0;
    
    // first 20 bytes are the filetype
    char filetype[20];
    memcpy(filetype, buffer->data(), 20);
    filemark += 21; // next byte we will get will be byte 21

    std::cout << "filetype: " << filetype << std::endl;

    filemark += 2; // we dont know the meaning of the next 2 bytes

    unsigned int version; // 4 byte unsigned int
    memcpy(&version, buffer->data() + filemark, 4);
    filemark += 4;

    std::cout << "version: " << version << std::endl;

    NODE rootObject;
    // next 4 bytes is the offset from the start of the file to the end of this node
    memcpy(&(rootObject.endOffset), buffer->data() + filemark, 4);
    filemark += 4;

    memcpy(&(rootObject.numProperties), buffer->data() + filemark, 4);
    filemark += 4;

    memcpy(&(rootObject.propertyListLen), buffer->data() + filemark, 4);
    filemark += 4;

    memcpy(&(rootObject.nameLen), buffer->data() + filemark, 1);
    filemark += 1;

    rootObject.name = (char*)malloc((rootObject.nameLen + 1) * sizeof(char));
    std::cout << (unsigned int)rootObject.nameLen << std::endl;
    if (rootObject.name == NULL) {
        throw std::runtime_error("failed to allocate memory for fbx file node name");
    }
    rootObject.name[rootObject.nameLen] = '\0';
    memcpy(rootObject.name, buffer->data() + filemark, rootObject.nameLen);
    filemark += rootObject.nameLen;

    // read the properties of the node
    rootObject.properties = (PROPERTY*)malloc(sizeof(PROPERTY) * rootObject.propertyListLen);
    
    for (unsigned int i = 0; i < rootObject.propertyListLen; i++) {
        PROPERTY newProp;
        char typeCode;
        memcpy(&typeCode, buffer->data() + filemark, 1);
        filemark += 1;
        switch (typeCode) {
            case 'Y': {
                // 2 byte signed int
                newProp.data = malloc(sizeof(char) * 2);
                memcpy(newProp.data, buffer->data() + filemark, 2);
                filemark += 2;
                break;
            }
            case 'C': {
                // 1 bit boolean encoded as LSB of 1 byte
                newProp.data = malloc(sizeof(char) * 1);
                memcpy(newProp.data, buffer->data() + filemark, 1);
                filemark += 1;
                break;
            }
            case 'I': {
                // 4 byte signed int
                newProp.data = malloc(sizeof(char) * 4);
                memcpy(newProp.data, buffer->data() + filemark, 4);
                filemark += 4;
                break;
            }
            case 'F': {
                // 4 byte single precision IEEE 754 floating point number
                newProp.data = malloc(sizeof(char) * 4);
                memcpy(newProp.data, buffer->data() + filemark, 4);
                filemark += 4;
                break;
            }
            case 'D': {
                // 8 byte double precision IEEE 754 floating point number
                newProp.data = malloc(sizeof(char) * 8);
                memcpy(newProp.data, buffer->data() + filemark, 8);
                filemark += 8;
                break;
            }
            case 'L': {
                // 8 byte signed integer
                newProp.data = malloc(sizeof(char) * 8);
                memcpy(newProp.data, buffer->data() + filemark, 8);
                filemark += 8;
                break;
            }
            case 'R': // raw binary data
            case 'S': {
                SPECIAL_TYPE* newSpecial = (SPECIAL_TYPE*)malloc(sizeof(SPECIAL_TYPE));
                memcpy(&(newSpecial->length), buffer->data() + filemark, 4);
                filemark += 4;
                // string is not NULL terminated but may contain null characters that are used in fbx
                newSpecial->data = (char*)malloc(sizeof(char) * newSpecial->length);
                filemark += newSpecial->length;
                break;
            }
            case 'f': // array of 4 byte single precision IEEE floats
            case 'd': // array of 8 byte double precision IEEE floats
            case 'l': // array of 8 byte signed ints
            case 'i': // array of 4 byte signed ints
            case 'b': { // array of 1 byte boolean
                unsigned int arrayTypeSize = 0;
                switch(typeCode) {
                    case 'f':
                        arrayTypeSize = 4;
                        break;
                    case 'd':
                        arrayTypeSize = 8;
                        break;
                    case 'l':
                        arrayTypeSize = 8;
                        break;
                    case 'i':
                        arrayTypeSize = 4;
                        break;
                    case 'b':
                        arrayTypeSize = 1;
                }
                // array of 4 byte single precision IEEE 754 floats
                ARRAY_TYPE* array = (ARRAY_TYPE*)malloc(sizeof(ARRAY_TYPE));
                memcpy(&(array->arrayLength), buffer->data() + filemark, 4);
                filemark += 4;
                memcpy(&(array->encoding), buffer->data() + filemark, 4);
                filemark += 4;
                memcpy(&(array->compressedLength), buffer->data() + filemark, 4);
                filemark += 4;

                // get contents of array
                unsigned int allocSize = 0;
                if (array->encoding == 0) { // data is not compressed
                    allocSize = sizeof(char) * arrayTypeSize * array->arrayLength;
                    array->data = malloc(allocSize);
                    for (unsigned int j = 0; j < array->arrayLength; j++) {
                        memcpy((char*)array->data + (j * arrayTypeSize), buffer->data() + filemark, arrayTypeSize);
                        filemark += arrayTypeSize;
                    }
                }
                if (array->encoding == 1) { // data is compressed
                    allocSize = sizeof(char) * array->compressedLength;
                }
                break;
            }
        }
        rootObject.properties[i] = newProp;
    }

    std::cout << "endOffset: " << rootObject.endOffset << std::endl 
        << "numProperties: " << rootObject.numProperties << std::endl
        << "propertyListLen: " << rootObject.propertyListLen << std::endl
        << "nameLen: " << (unsigned int)rootObject.nameLen << std::endl
        << "name: " << rootObject.name << std::endl;
    

    // make sure that all neccesary data is freed, if its not this will cause huge memory leaks

}

unsigned char* FileHandler::loadImage(const char* filepath, int& width, int& height, int& numChannels) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filepath, &width, &height, &numChannels, 0);

    return data;
}

