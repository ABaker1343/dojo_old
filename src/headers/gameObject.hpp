#ifndef __HEADER_GAME_OBJECT
#define __HEADER_GAME_OBJECT

#include <glm/glm.hpp>

namespace dojo {
    class GameObject {
        public:
            GameObject();
            ~GameObject();

            glm::vec3 pos;
            glm::vec3 scale;

        private:

    };
}

#endif
