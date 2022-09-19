#include "headers/window.hpp"
#include "freetype/freetype.h"
#include <GLFW/glfw3.h>

namespace dojo {

bool Window::KEYS[KEYS_SIZE];
bool Window::MOUSE_BUTTONS[MOUSE_BUTTONS_SIZE];
int Window::winHeight, Window::winWidth;
double Window::MOUSE_POSITION_X, Window::MOUSE_POSITION_Y;

Window::Window(int width, int height, const char* name) {

    // initalize glfw and the window

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    winHeight = height; winWidth = width;

    window = glfwCreateWindow(
            winHeight, winHeight, name,
            NULL, NULL
    );

    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);

    //initalize opengl

}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::windowResizeCallback(GLFWwindow* window, int width, int height) {
    winWidth = width, winHeight = height;
    glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (action) {
        case GLFW_PRESS:
            KEYS[key] = true;
            break;
        case GLFW_RELEASE:
            KEYS[key] = false;
            break;
        default:
            break;
    }
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    switch(action) {
        case GLFW_PRESS:
            MOUSE_BUTTONS[button] = true;
            break;
        case GLFW_RELEASE:
            MOUSE_BUTTONS[button] = false;
            break;
        default:
            break;
    }
}

void Window::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    MOUSE_POSITION_X = xpos;
    MOUSE_POSITION_Y = ypos;
}

bool Window::isAlive() {
    return ! glfwWindowShouldClose(window);
}

void Window::setKill() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::showPointer() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::hidePointer() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

}

