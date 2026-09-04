#pragma once

#include "matrix_float4x4.hpp"
namespace Camera {
    class Camera{
        private:
            static glm::mat4 proj;
            static glm::mat4 view;
            static float scale,zNear,zFar;
            static float curX,curY;
        public:
            static void init(float x, float y, float znear=-10.0f, float zfar=10.0f);
            static void move(int cameraX, int cameraY);
            static glm::mat4 getVP();
            static void updateProjection();
            static void zoomIn(float s);
            static void zoomOut(float s);

    };

}
