#ifndef __HEADER_GAME_OBJECT
#define __HEADER_GAME_OBJECT

#include <glm/glm.hpp>

namespace dojo {
    class GameObject {
        public:
            GameObject();
            ~GameObject();

            int flip;
            glm::vec3 pos;
            glm::vec3 scale;

        private:

    };
}

#endif
