#pragma once
#include <GLFW/glfw3.h>

namespace Keylistener {
    void keyCallback(GLFWwindow* instance, int key, int scancode, int action, int mods);
    bool isKeyPressed(int key);
    bool isKeyPressedOnce(int key);
    void endFrame();

}
