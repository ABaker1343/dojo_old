#ifndef __HEADER_GAME_OBJECT_2D_ANIMATED_SPRITE
#define __HEADER_GAME_OBJECT_2D_ANIMATED_SPRITE

#include "gameObject.hpp"
#include "renderable.hpp"

#include <string>

namespace dojo {

class GameObject2DAnimatedSprite : public GameObject, public Renderable {
    public:
        GameObject2DAnimatedSprite(int numFrames, std::string animationPath);
        ~GameObject2DAnimatedSprite();

        bool nextFrame();

        int currentFrame();
        float currentAnimationChunkSize();
        unsigned int currentTexture();

        typedef struct ANIMATION_DATA {
            int numFrames;
            int currentFrame;
            float chunkSize;
            unsigned int texture;
            unsigned int vertexBuffer;
        } ANIMATION;

    private:
        std::vector<ANIMATION> *animations;
        ANIMATION *currentAnimation;
};

}

#endif
