#include "Sprite.h"
#include "SpriteComponent.h"
#include "gl.h"
#include <GLFW/glfw3.h>
#include <unordered_set>
#include <iostream>

#include "Texture.h"
#include "Window.h"
#include "Renderbatch.h"
#include "KeyListener.h"
#include "MouseListener.h"
#include "Sound.h"
#include "imgui.h"
#include "Framebuffer.h"
#include "Camera.h"

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
        glDisable(GL_DEPTH_TEST);
        Camera::Camera::init(getWidth(), getHeight());
        Sound::SoundSystem::init();
        getImgui().init(getWindow());
        return true;
    }

    void run(){
        if (!init()){
            return;
        }

        constexpr int size=1000;
        Renderer::Renderbatch<size> batch;

        for (int i=0;i<10;i++){
            batch.addQuadWithTexAndID(50.0f*i, 50.0f*i, i ,50.0f);
        }

        batch.setIsDynamic(true);
        batch.setShader("res/Shaders/square.vert", "res/Shaders/square.frag");

        int sampler[10] = {0,1,2,3,4,5,6,7,8,9};

        batch.getShader().bind();
        batch.getShader().uploadArray<10>("textures", sampler);
        batch.getShader().unbind();

        Framebuffer::Framebuffer viewportFBO;
        ImVec2 viewportSize = ImVec2(getWidth(), getHeight());
        viewportFBO.create(viewportSize.x, viewportSize.y);

        Sprite spr;
        Texture::Texture tex;
        tex.create("res/Textures/idk.png");
        SpriteComponent comp;
        comp.setTexturePtr(tex);
        spr.addComponent(&comp);

        while (!glfwWindowShouldClose(instance)){
            glfwPollEvents();
            tex.bind(1);

            getImgui().startFrame();
            spr.Imgui();
            {
                ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
                ImGui::Begin("Game Viewport");
                ImVec2 panelSize = ImGui::GetContentRegionAvail();

                if (panelSize.x > 0 && panelSize.y > 0 &&
                    (panelSize.x != viewportSize.x || panelSize.y != viewportSize.y)) {
                        viewportSize = panelSize;
                        viewportFBO.destroy();
                        viewportFBO.create(viewportSize.x, viewportSize.y);
                        Camera::Camera::init(viewportSize.x, viewportSize.y);
                    }

                if (viewportSize.x > 0 && viewportSize.y > 0) {
                        viewportFBO.bind();
                        glViewport(0, 0, (GLsizei)viewportSize.x, (GLsizei)viewportSize.y);

                        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                        batch.draw();

                        viewportFBO.unbind();
                    }

                if (viewportSize.x > 0 && viewportSize.y > 0) {
                        uintptr_t texID = viewportFBO.getTexId();
                        ImGui::Image(reinterpret_cast<void*>(texID), viewportSize, ImVec2(0, 1), ImVec2(1, 0));
                    }

                ImGui::End();
                ImGui::PopStyleVar();
            }

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            getImgui().render();

            tex.unbind();
            Keylistener::endFrame();
            MouseListener::endFrame();

            glfwSwapBuffers(instance);
        }
        Sound::SoundSystem::destroy();
        getImgui().destroy();
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

    Imgui::Imgui getImgui(){
        static Imgui::Imgui s_instance;
        return s_instance;
    }

    unsigned long long getCounter(){
        static long long counter;
        counter++;
        return counter-1;
    }
}
