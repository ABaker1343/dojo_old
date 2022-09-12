#ifndef __HEADER_GAME_OBJECT
#define __HEADER_GAME_OBJECT

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace dojo {
    class GameObject {
        public:
            GameObject();
            ~GameObject();

            int flip;
            glm::mat4 transform;
            //glm::vec3 pos;
            //glm::vec3 scale;
            
            void setPos(float x, float y, float z=0.f);
            glm::vec3 getPos();

            void setScale(float x, float y, float z=0);
            glm::vec3 getScale();

        private:

    };
}

#endif
