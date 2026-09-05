#include "stb_image.h"
#include "EditorWindow.h"
#include "imgui.h"
#include "SpriteSheet.h"
#include <string>

namespace editor {
    void Imgui(){
        static char buf[100]="res/Textures/spritesheet.png";
        static char* name=buf;
        static char vBuffer[100]="res/Shaders/tex.vert";
        static char fBuffer[100]="res/Shaders/tex.frag";

        static char* vPath=vBuffer;
        static char* fPath=fBuffer;
        static Renderer::SpriteSheet<100> sprSheet;

        static int sW=16,sH=16;
        static int width = 0, height = 0, channels = 0;
        static int count;
        static bool done=false,firstTime=true;
        static float tSize=32.0f,dScale=1.0f;

        ImGui::Begin("Controls");
        ImGui::DragFloat("Tile Size", &tSize);
        ImGui::DragFloat("Display Scale", &dScale);
        ImGui::End();


        ImGui::Begin("Editor");
        ImGui::Checkbox("Upload?", &done);
        if (done){
            if (firstTime){
                if (stbi_info(name, &width, &height, &channels)){
                    sprSheet.create(width, height,sW,sH, 4, name,vPath, fPath);
                    firstTime=false;
                }
            }

            auto data = sprSheet.getData();
            ImTextureRef texRef((ImTextureID)(intptr_t)sprSheet.getTexture().getId());

            float buttonSize = tSize * dScale;
            float windowVisibleX = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
            for (int i=0;i<count;i++){
                if (i >= data.size()) continue;
                ImVec2 uv0,uv1;

                uv0 = ImVec2(data[i][4], data[i][7]);
                uv1 = ImVec2(data[i][5], data[i][6]);
                ImGui::PushID(i);
                if (ImGui::ImageButton(std::to_string(i).c_str(),texRef, ImVec2(buttonSize, buttonSize), uv0, uv1)){

                }
                ImGui::PopID();
                float lastButtonX = ImGui::GetItemRectMax().x;
                float nextButtonX = lastButtonX + 10.0f + buttonSize;

                if (i + 1 < count && nextButtonX < windowVisibleX) {
                    ImGui::SameLine();
                }
            }
        }
        else {
            ImGui::InputText("Add spritesheet", name, 100);
            ImGui::InputText("Shader Vertex Path", vPath, 100);
            ImGui::InputText("Shader Fragment Path", fPath, 100);
            ImGui::Text("Max Counts are 100");
            ImGui::DragInt("Count", &count);
            ImGui::DragInt("Sprite width", &sW);
            ImGui::DragInt("Sprite Height", &sH);
            if (width || height || channels){
                sprSheet.destroy();
                firstTime=true;
                width = 0;
                height = 0;
                channels = 0;
            }
        }
        ImGui::End();

    }
}
