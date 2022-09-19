#ifndef __HEADER_MENU_ITEM
#define __HEADER_MENU_ITEM

#include <glm/glm.hpp>
#include <string>

#include "../../headers/renderable.hpp"

namespace dojo {

class MenuItem : public Renderable {
public:
    MenuItem(std::string _content, glm::vec4 _pos, glm::vec3 _backgroundColor, glm::vec3 _textColor = glm::vec3(1.f, 1.f, 1.f));
    MenuItem(unsigned int _texture, glm::vec4 _pos);

    ~MenuItem();

    glm::vec4 screenPos;
    glm::vec3 backgroundColor;
    glm::vec3 textColor;

    std::string content;

    unsigned int texture = 0;
};

}

#endif
