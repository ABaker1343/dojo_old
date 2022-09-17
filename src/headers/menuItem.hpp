#ifndef __HEADER_MENU_ITEM
#define __HEADER_MENU_ITEM

#include <glm/glm.hpp>

namespace dojo {

class MenuItem {
public:
    MenuItem(glm::vec2 pos);

    ~MenuItem();

    glm::vec2 screenPos;
};

}

#endif
