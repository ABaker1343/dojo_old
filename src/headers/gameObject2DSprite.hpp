#ifndef __HEADER_GAME_OBJECT_2D_SPRITE
#define __HEADER_GAME_OBJECT_2D_SPRITE

#include "gameObject.hpp"
#include "renderable.hpp"

namespace dojo {

class GameObject2DSprite : public GameObject, public Renderable {
    public:
        GameObject2DSprite(std::string spritePath);
        ~GameObject2DSprite();

        int numElements();


    private:

};

}

#endif
