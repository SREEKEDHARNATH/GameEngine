#include "Camera.h"
#include "matrix_clip_space.hpp"
#include "matrix_transform.hpp"

namespace Camera {

    void Camera::init(float x, float y, float znear, float zfar){
        proj = glm::ortho(0.0f, x, 0.0f, y, znear, zfar);
        view = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
    }
    void Camera::move(int cameraX, int cameraY){
        view = glm::translate(view, glm::vec3(cameraX, cameraY, 0.0f));
    }
    glm::mat4 Camera::getVP(){
        return proj*view;
    }
    glm::mat4 Camera::view = glm::mat4(0);
    glm::mat4 Camera::proj;

}
