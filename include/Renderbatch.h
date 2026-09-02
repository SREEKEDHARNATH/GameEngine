#pragma once
#include "Camera.h"
#include "Renderer.h"
#include "Shader.h"
#include "VBLayout.h"
#include <array>

namespace Renderer {

    template<int maxSize>
    class Renderbatch{
        private:
            float buffer[maxSize];
            unsigned int indices[maxSize];

            Renderer::vertexBuffer<float> vbo;
            Renderer::indexBuffer<unsigned int> ebo;
            Shader::shader shader;
            Renderer::vertexArray vao;
            VBLayout vblayout;
            int curIndex=0,elemsCount=0;
            int curIndexOfBuffer=0;
            int prvCurIndex=0;
            bool firstTime=true,firstLayout=true;



        public:
            void setShader(const char* vPath, const char* fPath){
                shader.destroy();
                shader.create(vPath, fPath);
            }
            void setLayout(const VBLayout& layout) {
                if (!firstLayout) return;
                vblayout = layout;
                firstLayout=false;
            }
            template<int elemsPerVertex>
            void addQuad(std::array<std::array<float, elemsPerVertex>, 4>& vertices) {
                if ((4*elemsPerVertex)+curIndexOfBuffer >= maxSize ) return;
                using Vertex = std::array<float, elemsPerVertex>;

                for (int i = 0; i < 4; i++) {
                    const Vertex& vertex = vertices[i];
                    for (int j = 0; j < elemsPerVertex; j++) {
                        buffer[curIndexOfBuffer++] = vertex[j];
                    }
                }

                updateIndexBuffer();
            }

            void addQuadWithPos(float x, float y, float size){
                std::array<std::array<float, 2>, 4> vertices;
                vertices[0] = {x, y};
                vertices[1] = {x+size, y};
                vertices[2] = {x+size,y+size};
                vertices[3] = {x, y+size};

                VBLayout layout;
                layout.push<float>(2);
                setLayout(layout);
                addQuad<2>(vertices);
            }

            void addQuadWithColor(float x, float y, float r, float g, float b, float a, float size){
                std::array<std::array<float, 6>, 4> vertices;
                vertices[0] = {x, y, r, g, b, a};
                vertices[1] = {x+size, y, r, g, b, a};
                vertices[2] = {x+size,y+size, r, g, b, a};
                vertices[3] = {x, y+size, r, g, b, a};

                VBLayout layout;
                layout.push<float>(2);
                layout.push<float>(4);
                setLayout(layout);
                addQuad<6>(vertices);
            }

            void addQuadWithTex(float x, float y, float size){
                std::array<std::array<float, 4>, 4> vertices;
                vertices[0] = {x, y, 1.0f, 1.0f};
                vertices[1] = {x+size, y, 1.0f, 0.0f};
                vertices[2] = {x+size,y+size, 0.0f, 0.0f};
                vertices[3] = {x, y+size, 0.0f, 1.0f};

                VBLayout layout;
                layout.push<float>(2);
                layout.push<float>(2);
                setLayout(layout);
                addQuad<4>(vertices);
            }

            void addQuadWithTexAndID(float x, float y, float id, float size){
                std::array<std::array<float, 5>, 4> vertices;
                vertices[0] = {x, y, 1.0f, 1.0f, id};
                vertices[1] = {x+size, y, 1.0f, 0.0f, id};
                vertices[2] = {x+size,y+size, 0.0f, 0.0f, id};
                vertices[3] = {x, y+size, 0.0f, 1.0f, id};

                VBLayout layout;
                layout.push<float>(2);
                layout.push<float>(2);
                layout.push<float>(1);
                setLayout(layout);
                addQuad<5>(vertices);
            }

            void updateIndexBuffer(){
                indices[elemsCount + 0] = curIndex + 0;
                indices[elemsCount + 1] = curIndex + 1;
                indices[elemsCount + 2] = curIndex + 2;
                indices[elemsCount + 3] = curIndex + 2;
                indices[elemsCount + 4] = curIndex + 3;
                indices[elemsCount + 5] = curIndex + 0;
                curIndex+=4;
                elemsCount+=6;

            }

            void draw(){
                if (elemsCount==0) return;
                vao.bind();

                if (prvCurIndex != curIndex || firstTime){
                    if (firstTime){
                        vbo.init(buffer, maxSize * sizeof(float));
                        ebo.init(indices, maxSize * sizeof(unsigned int));
                        vbo.bind();
                        vao.addVbo(vbo, vblayout);
                    }
                    else {
                        vbo.addSubBuffer(buffer, curIndexOfBuffer * sizeof(float), 0);
                        ebo.addSubBuffer(indices, elemsCount * sizeof(unsigned int), 0);
                        vbo.bind();
                    }


                    ebo.bind();
                    firstTime=false;
                }
                else {
                    vbo.bind();
                    ebo.bind();
                }

                shader.bind();
                shader.uploadMat4f("u_VP", Camera::Camera::getVP());
                glDrawElements(GL_TRIANGLES, elemsCount, GL_UNSIGNED_INT, nullptr);

                vao.unbind();
                vbo.unbind();
                ebo.unbind();

                prvCurIndex = curIndex;

            }

            void clear(){
                curIndex=0;
                prvCurIndex=0;
                curIndexOfBuffer=0;
                elemsCount=0;


            }
    };

}
