#pragma once
#include <GLFW/glfw3.h>

namespace MouseListener{
     void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
     void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
     void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

     bool isButtonPressed(int button);
     bool isDragging(int button);
     bool isDragging();
     bool isScrolling();

     double getX();
     double getY();
     double getScrollX();
     double getScrollY();


     void endFrame();
}
