#pragma once
#include <GLFW/glfw3.h>

namespace Window{
    bool init();
    void run();
    GLFWwindow* getWindow();

    int getWidth();
    int getHeight();
    const char* getTitle();


}
