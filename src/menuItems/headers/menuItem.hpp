#ifndef __HEADER_MENU_ITEM
#define __HEADER_MENU_ITEM

#include <glm/glm.hpp>
#include <string>

#include "../../headers/renderable.hpp"

namespace dojo {

class MenuItem : public Renderable {
public:
    MenuItem(glm::vec4 pos, glm::vec3 _backgroundColor, std::string _content);

    ~MenuItem();

    glm::vec4 screenPos;
    glm::vec3 backgroundColor;

    std::string content;
};

}

#endif
