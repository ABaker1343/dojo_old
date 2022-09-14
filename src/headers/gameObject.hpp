#ifndef __HEADER_GAME_OBJECT
#define __HEADER_GAME_OBJECT

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace dojo {
    class GameObject {
        public:
            GameObject(glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
            ~GameObject();

            int flip;
            glm::mat4 transform;
            //glm::vec3 pos;
            //glm::vec3 scale;
            
            void move(float x, float y, float z=0.f);
            glm::vec3 getPos();

            void scale(float x, float y, float z=0);
            glm::vec3 getScale();

            void rotate(float degrees, glm::vec3 axis);

            glm::mat4 getTransform();

        private:

    };
}

#endif
