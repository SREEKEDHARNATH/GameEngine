#include "MouseListener.h"
#include <GLFW/glfw3.h>

constexpr int size=3;
int buttons[size];
double x,y,scrollX,scrollY;
bool posChanged;


namespace MouseListener{
    bool isValid(int button){
        return (button >= 0 && button < size);
    }
     void mousePosCallback(GLFWwindow* window, double xpos, double ypos){
         x=xpos;
         y=ypos;
         posChanged = true;
     }

     void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
         if (isValid(button)){
             if (action == GLFW_PRESS){
                 buttons[button] = true;

             }
             else if (action == GLFW_RELEASE){
                 buttons[button] = false;

             }

         }
     }

     void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset){
         scrollX += xoffset;
         scrollY += yoffset;
     }

     bool isButtonPressed(int button){
         if (isValid(button)){
             return buttons[button];
         }
         return false;
     }

     bool isDragging(int button){
         if (isValid(button)){
             return posChanged && isButtonPressed(button);
         }
         return false;
     }

     bool isDragging(){
         return isDragging(GLFW_MOUSE_BUTTON_LEFT) || isDragging(GLFW_MOUSE_BUTTON_MIDDLE) || isDragging(GLFW_MOUSE_BUTTON_RIGHT);;

     }

     bool isScrolling(){
         return scrollX != 0 || scrollY != 0;
     }


     double getX(){
         return x;
     }

     double getY(){
         return y;
     }

     double getScrollX(){
         return scrollX;
     }

     double getScrollY(){
         return scrollY;
     }

     void endFrame(){
         scrollX=0;
         scrollY=0;
     }
}
