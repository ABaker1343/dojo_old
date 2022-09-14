#include "headers/gameObject2DAnimatedSprite.hpp"
#include "headers/gameObject.hpp"

namespace dojo {

GameObject2DAnimatedSprite::GameObject2DAnimatedSprite(int numFrames, std::string animationPath,
        glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {

    animations = new std::unordered_map<std::string, ANIMATION>();
    ANIMATION baseAnimation;

    baseAnimation.name = "default";
    baseAnimation.currentFrame = 0;
    baseAnimation.numFrames = numFrames;
    baseAnimation.chunkSize = 1.0f/numFrames;

    vertices = new std::vector<float> {
        // x, y, z, texture x, texture y
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, baseAnimation.chunkSize, 1.0f,
        1.0f, 0.0f, 0.0f, baseAnimation.chunkSize, 0.0f,
    };

    elements = new std::vector<unsigned int> {
        0, 1, 2,
        2, 3, 0,
    };

    Renderable::createTexturedObjectBuffers(vertexArrayObject, baseAnimation.vertexBuffer, elementBuffer,
            vertices, elements);
    shaderProgram = Renderable::createBasicShaderProgram("src/shaders/basic2DVert.vert", "src/shaders/basic2DFrag.frag");
    baseAnimation.texture = Renderable::loadTextureFromFile(animationPath.c_str());

    animations->insert({"default", baseAnimation});
    currentAnimation = &(*animations)["default"];

    flip = 0;
    isCopy = false;

}

GameObject2DAnimatedSprite::GameObject2DAnimatedSprite(GameObject2DAnimatedSprite *obj,
        glm::vec3 pos, glm::vec3 scale) : GameObject(pos, scale) {
    animations = obj->animations;
    currentAnimation = &(*animations)["default"];
    elementBuffer = obj->elementBuffer;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, (*animations)["default"].vertexBuffer);
    flip = obj->flip;

    isCopy = true;
}

GameObject2DAnimatedSprite::~GameObject2DAnimatedSprite() {
    if (!isCopy) {
        delete vertices;
        delete elements;
        delete animations;
    }
        
}

int GameObject2DAnimatedSprite::currentFrame() {
    return currentAnimation->currentFrame;
}

float GameObject2DAnimatedSprite::currentAnimationChunkSize() {
    return currentAnimation->chunkSize;
}

unsigned int GameObject2DAnimatedSprite::currentTexture() {
    return currentAnimation->texture;
}

std::string GameObject2DAnimatedSprite::currentAnimationName() {
    return currentAnimation->name;
}

void GameObject2DAnimatedSprite::addAnimation(std::string animationName, int numFrames, std::string animationPath) {
    ANIMATION newAnimation;
    newAnimation.name = animationName;
    newAnimation.currentFrame = 0;
    newAnimation.numFrames = numFrames;
    newAnimation.chunkSize = 1.0f/numFrames;

    vertices = new std::vector<float> {
        // x, y, z, texture x, texture y
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, newAnimation.chunkSize, 1.0f,
        1.0f, 0.0f, 0.0f, newAnimation.chunkSize, 0.0f,
    };

    // we only have to have one new framebuffer here
    newAnimation.vertexBuffer = Renderable::createVertexBuffer(vertices);

    newAnimation.texture = Renderable::loadTextureFromFile(animationPath.c_str());
    
    animations->insert({animationName, newAnimation});
}

void GameObject2DAnimatedSprite::setCurrentAnimation(std::string animationName) {
    currentAnimation->currentFrame = 0;
    currentAnimation = &(*animations)[animationName];
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, currentAnimation->vertexBuffer);
}

bool GameObject2DAnimatedSprite::nextFrame() {
    // move the animation along one frame
    // return true if there is another frame and false if the animation has finished
    if (currentAnimation->currentFrame >= currentAnimation->numFrames-1) {
        currentAnimation->currentFrame = 0;
        return false;
    }
    currentAnimation->currentFrame++;
    return true;
}

}
