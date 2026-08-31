#include "GLFW/glfw3.h"

constexpr int size=350;
bool keys[size];
bool keysPressedOnce[size];


namespace Keylistener {

    bool isValid(int key){
        return (key >= 0 && key < size);
    }

    void keyCallback(GLFWwindow* instance, int key, int scancode, int action, int mods){
        if (isValid(key)){
            if (action == GLFW_PRESS){
                keys[key] = true;
                keysPressedOnce[key] = true;
            }
            else if (action == GLFW_RELEASE){
                keys[key] = false;
            }

        }

    }

    bool isKeyPressed(int key){
        if (!isValid(key)) return false;
        return keys[key];
    }

    bool isKeyPressedOnce(int key){
        if (!isValid(key)) return false;
        return keysPressedOnce[key];
    }

    void endFrame(){
        for (int i=0;i<size;i++){
            keysPressedOnce[i]=false;
        }
    }
}
