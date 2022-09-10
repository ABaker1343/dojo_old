#include "headers/window.hpp"
#include "headers/renderable.hpp"

namespace dojo {

bool Window::KEYS[KEYS_SIZE];

Window::Window(int width, int height, const char* name) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(
            width, height, name,
            NULL, NULL
    );

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("failed to load opengl functions");
    }

    // allow color blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, width, height);
    
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    
    createCollisionBoxRenderDependancies();

}

Window::~Window() {
    delete boxElements;
    delete boxVertices;

    glDeleteBuffers(1, &boxElementBuffer);
    glDeleteBuffers(1, &collisionBoxVertexBuffer);
    glDeleteVertexArrays(1, &collisionBoxVertexArray);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::windowResizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        KEYS[key] = true;
    }
    if (action == GLFW_RELEASE) {
        KEYS[key] = false;
    }
}

bool Window::isAlive() {
    return ! glfwWindowShouldClose(window);
}

void Window::clear() {
    glfwSwapBuffers(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
}

void Window::render2D(Camera2D *c, GameObject2DSprite *s) {
    glUseProgram(s->shaderProgram);
    glBindVertexArray(s->vertexArrayObject);

    glBindTexture(GL_TEXTURE_2D, s->texture);

    int flipUniformPos = glGetUniformLocation(s->shaderProgram, "flip");
    glUniform1i(flipUniformPos, s->flip);

    int worldPosUniformLocation = glGetUniformLocation(s->shaderProgram, "worldPos");
    glUniform3fv(worldPosUniformLocation, 1, glm::value_ptr(s->pos));

    int scaleUniformLocation = glGetUniformLocation(s->shaderProgram, "objectScale");
    glUniform3fv(scaleUniformLocation, 1, glm::value_ptr(s->scale));

    int cameraPosUniformLocation = glGetUniformLocation(s->shaderProgram, "cameraPos");
    glUniform3fv(cameraPosUniformLocation, 1, glm::value_ptr(c->pos));

    int cameraScaleUniformLocation = glGetUniformLocation(s->shaderProgram, "cameraScale");
    glUniform3fv(cameraScaleUniformLocation, 1, glm::value_ptr(c->scale));

    int animationFrameUniformLocation = glGetUniformLocation(s->shaderProgram, "animationFrame");
    glUniform1i(animationFrameUniformLocation, 0);

    int animationChunkSizeUniformLocation = glGetUniformLocation(s->shaderProgram, "animationChunkSize");
    glUniform1i(animationChunkSizeUniformLocation, 1.0f);

    glDrawElements(GL_TRIANGLES, s->numElements(), GL_UNSIGNED_INT, 0);
}

void Window::render2D(Camera2D *c, GameObject2DAnimatedSprite *s) {
    glUseProgram(s->shaderProgram);
    glBindVertexArray(s->vertexArrayObject);

    glBindTexture(GL_TEXTURE_2D, s->currentTexture());

    int flipUniformPos = glGetUniformLocation(s->shaderProgram, "flip");
    glUniform1i(flipUniformPos, s->flip);

    int worldPosUniformLocation = glGetUniformLocation(s->shaderProgram, "worldPos");
    glUniform3fv(worldPosUniformLocation, 1, glm::value_ptr(s->pos));

    int scaleUniformLocation = glGetUniformLocation(s->shaderProgram, "objectScale");
    glUniform3fv(scaleUniformLocation, 1, glm::value_ptr(s->scale));

    int cameraPosUniformLocation = glGetUniformLocation(s->shaderProgram, "cameraPos");
    glUniform3fv(cameraPosUniformLocation, 1, glm::value_ptr(c->pos));

    int cameraScaleUniformLocation = glGetUniformLocation(s->shaderProgram, "cameraScale");
    glUniform3fv(cameraScaleUniformLocation, 1, glm::value_ptr(c->scale));

    int animationFrameUniformLocation = glGetUniformLocation(s->shaderProgram, "animationFrame");
    glUniform1i(animationFrameUniformLocation, s->currentFrame());

    int animationChunkSizeUniformLocation = glGetUniformLocation(s->shaderProgram, "animationChunkSize");
    glUniform1f(animationChunkSizeUniformLocation, s->currentAnimationChunkSize());

    glDrawElements(GL_TRIANGLES, s->numElements(), GL_UNSIGNED_INT, 0);
}

void Window::render2D(Camera2D *c, GameObject2DCollisionBox *b) {
    glUseProgram(collisionBox2DShaderProgram);
    glBindVertexArray(collisionBoxVertexArray);
    
    //int flipUniformPos = glGetUniformLocation(collisionBox2DShaderProgram, "flip");
    //glUniform1i(flipUniformPos, b->flip);

    int worldPosUniformLocation = glGetUniformLocation(collisionBox2DShaderProgram, "worldPos");
    glUniform3fv(worldPosUniformLocation, 1, glm::value_ptr(*b->objPos));

    int scaleUniformLocation = glGetUniformLocation(collisionBox2DShaderProgram, "objectScale");
    glUniform3fv(scaleUniformLocation, 1, glm::value_ptr(*b->objScale));

    int cameraPosUniformLocation = glGetUniformLocation(collisionBox2DShaderProgram, "cameraPos");
    glUniform3fv(cameraPosUniformLocation, 1, glm::value_ptr(c->pos));

    int cameraScaleUniformLocation = glGetUniformLocation(collisionBox2DShaderProgram, "cameraScale");
    glUniform3fv(cameraScaleUniformLocation, 1, glm::value_ptr(c->scale));

    int offsetLocation = glGetUniformLocation(collisionBox2DShaderProgram, "offset");
    int scaleLocation = glGetUniformLocation(collisionBox2DShaderProgram, "scale");

    glUniform3fv(offsetLocation, 1, glm::value_ptr(b->relativeOffset));
    glUniform3fv(scaleLocation, 1, glm::value_ptr(b->relativeScale));

    glDrawElements(GL_TRIANGLES, boxElements->size(), GL_UNSIGNED_INT, 0);
}

void Window::createCollisionBoxRenderDependancies() {
    // create the buffers


    boxVertices = new std::vector<float> {
        0.0f, 0.0f, 0.0f,
        0.f, 1.f, 0.f,
        1.f, 1.f, 0.f,
        1.f, 0.f, 0.f,
    };

    boxElements = new std::vector<unsigned int> {
        0, 1, 2,
        2, 3, 0
    };

    collisionBoxVertexBuffer = Renderable::createVertexBuffer(boxVertices);
    glGenVertexArrays(1, &collisionBoxVertexArray);
    glBindVertexArray(collisionBoxVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, collisionBoxVertexBuffer);
    glGenBuffers(1, &boxElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * boxElements->size(), boxElements->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0 );
    glEnableVertexAttribArray(0);
    
    // create shaders

    collisionBox2DShaderProgram = Renderable::createBasicShaderProgram("src/shaders/collisionBoxVert.vert", "src/shaders/collisionBoxFrag.frag");

}

}
