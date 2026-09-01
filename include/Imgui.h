#pragma once
#include <GLFW/glfw3.h>

namespace Imgui {
    class Imgui{
        public:
            void init(GLFWwindow* window, const char* glsl_version = "#version 460");
            void startFrame();
            void render();
            void destroy();
    };
}
