#pragma once

#include <glad/glad.h>
#include "GLFW/glfw3.h"
class GlfwWrapper
{
public:
    GLFWwindow* window;

    void init();
    int setupWindow(int w, int h);
};
