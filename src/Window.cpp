#include "gl.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <unordered_set>
#include "Renderbatch.h"
#include <iostream>
#include "KeyListener.h"
#include "MouseListener.h"

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const char* message, const void* userParam){

    static std::unordered_set<GLuint> loggedIDs;
    if (loggedIDs.find(id) != loggedIDs.end() || severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
        return;
    }

    loggedIDs.insert(id);
    std::cerr << "[OpenGL Error " << id << "] " << message << "\n";
}

namespace Window {
    GLFWwindow* instance;

    bool init(){
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW\n";
            return false;
        }
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        instance = glfwCreateWindow(getWidth(), getHeight(), getTitle(), nullptr, nullptr);

        glfwSetKeyCallback(instance, Keylistener::keyCallback);

        glfwSetMouseButtonCallback(instance, MouseListener::mouseButtonCallback);
        glfwSetCursorPosCallback(instance, MouseListener::mousePosCallback);
        glfwSetScrollCallback(instance, MouseListener::mouseScrollCallback);

        if (!instance){
            std::cerr << "Window creation failed\n";
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(instance);
        glfwSwapInterval(1);

        if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            glfwDestroyWindow(instance);
            glfwTerminate();
            return false;
        }

        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(MessageCallback, nullptr);
        }


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        return true;
    }

    void run(){
        if (!init()){
            return;
        }

        Shader::shader shader;
        shader.create("res/Shaders/square.vert", "res/Shaders/square.frag");

        Renderer::Renderbatch<1000> batch;
        batch.addQuadWithPos(-0.5f, -0.5f, 0.5f);

        batch.setShader(shader);

        while (!glfwWindowShouldClose(instance)){
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT);

            batch.draw();

            Keylistener::endFrame();
            MouseListener::endFrame();

            glfwSwapBuffers(instance);
        }

        glfwDestroyWindow(instance);
        glfwTerminate();
    }

    GLFWwindow* getWindow(){
        return instance;
    }


    int getWidth(){
        return 1024;
    }
    int getHeight(){
        return 576;
    }
    const char* getTitle(){
        return "Game";
    }
}
