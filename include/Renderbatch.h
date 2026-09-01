#include "Renderer.h"
#include "Shader.h"
#include "VBLayout.h"
#include <array>

namespace Renderer {

    class Renderbatch{
        private:
            float buffer[10000];
            unsigned int indices[15000];

            Renderer::vertexBuffer<float> vbo;
            Renderer::indexBuffer<unsigned int> ebo;
            Shader::shader shader;
            Renderer::vertexArray vao;
            VBLayout vblayout;
            int curIndex=0,elemsCount=0;
            int curIndexOfBuffer=0;
            int prvCurIndex=0,prvElemsCount=0;
            int prvCurIndexOfBuffer=0;



        public:
            void setShader(Shader::shader& SHADER){
                shader = SHADER;
            }
            void setLayout(const VBLayout& layout) {
                vblayout = layout;
            }
            template<int elemsPerVertex, int typesOfElemsInVertex>
            void addQuad(std::array<std::array<float, elemsPerVertex>, 4>& vertices) {
                using Vertex = std::array<float, elemsPerVertex>;


                for (int i = 0; i < 4; i++) {
                    const Vertex& vertex = vertices[i];
                    for (int j = 0; j < elemsPerVertex; j++) {
                        buffer[curIndexOfBuffer++] = vertex[j];
                    }
                }

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
                static bool firstTime=true;
                vao.bind();
                if ((prvCurIndex == curIndex && prvElemsCount == elemsCount && prvCurIndexOfBuffer == curIndexOfBuffer) || firstTime){

                    vbo.init(buffer, curIndexOfBuffer * sizeof(float));
                    vbo.bind();
                    vao.addVbo(vbo, vblayout);

                    ebo.init(indices, elemsCount * sizeof(unsigned int));
                    ebo.bind();
                    firstTime=false;
                }
                else {
                    vbo.bind();
                    ebo.bind();
                }

                shader.bind();

                glDrawElements(GL_TRIANGLES, elemsCount, GL_UNSIGNED_INT, nullptr);

                vao.unbind();
                vbo.unbind();
                ebo.unbind();


            }
    };

}
