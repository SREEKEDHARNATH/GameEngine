#include "Camera.h"
#include "matrix_clip_space.hpp"
#include "matrix_transform.hpp"

namespace Camera {

    void Camera::init(float x, float y, float znear, float zfar){
        scale=1.0f;
        zNear=znear;
        zFar=zfar;
        curX=x;
        curY=y;
        updateProjection();
    }
    void Camera::move(int cameraX, int cameraY){
        view = glm::translate(view, glm::vec3(cameraX, cameraY, 0.0f));
    }
    glm::mat4 Camera::getVP(){
        return proj*view;
    }
    void Camera::updateProjection() {
        proj = glm::ortho(0.0f, curX / scale, 0.0f, curY / scale, zNear, zFar);
    }

    void Camera::zoomIn(float s) {
        scale *= s;
        updateProjection();
    }

    void Camera::zoomOut(float s) {
        scale = std::max(0.001f, scale / s);
        updateProjection();
    }

    glm::mat4 Camera::view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );;

    glm::mat4 Camera::proj;
    float Camera::scale=1.0f;
    float Camera::zNear;
    float Camera::zFar;
    float Camera::curX;
    float Camera::curY;


}
