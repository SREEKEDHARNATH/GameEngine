#pragma once

#include "Renderbatch.h"
#include "Texture.h"
#include <array>
namespace Renderer {

    template<int count, int slot>
    class SpriteSheet{
        private:
            int texWidth,texHeight;
            int sprWidth,sprHeight;
            const char* filePath;
            std::array<std::array<float, 8>, count> data;
            Texture::Texture tex;
            Renderbatch<count * 9> batch;

        public:
            void create(int tW, int tH, int sW, int sH, const char* path, const char* vPath, const char* fPath){
                tex.create(path);
                texWidth = tW;
                texHeight = tH;
                sprWidth = sW;
                sprHeight = sH;
                filePath = path;

                int cols = tW/sW;
                int totalRows = tH / sH;

                for (int i = 0; i < count; i++) {
                    int col = i % cols;
                    int row = i / cols;

                    float left   = col * sW;
                    float right  = left + sW;

                    int flippedRow = (totalRows - 1) - row;

                    float bottom = (flippedRow * sH) / (float)tH;
                    float top    = ((flippedRow + 1) * sH) / (float)tH;


                    data[i] = {
                        left, right, (float)(row * sH), (float)((row + 1) * sH),left / (float)tW,right / (float)tW,bottom,top
                    };
                }
                VBLayout layout;
                layout.push<float>(2);
                layout.push<float>(2);
                layout.push<float>(1);
                batch.setLayout(layout);

                batch.setIsDynamic(true);
                batch.setShader(vPath, fPath);


            }
            template<int size> void addSamplers(const int (&samplers)[size], const char* name="textures"){
                auto s = batch.getShader();
                s.bind();
                s.template uploadArray<10>(name, samplers);
                s.unbind();
            }
            void queue(float x, float y, float size, int numOfSprite){
                std::array<std::array<float, 5>, 4> vertices;
                vertices[0] = {x, y, data[numOfSprite][4],data[numOfSprite][6], slot};
                vertices[1] = {x+size, y, data[numOfSprite][5], data[numOfSprite][6], slot};
                vertices[2] = {x+size,y+size, data[numOfSprite][5], data[numOfSprite][7], slot};
                vertices[3] = {x, y+size, data[numOfSprite][4], data[numOfSprite][7], slot};

                batch.template addQuad<5>(vertices);

            }
            void draw(){
                tex.bind(slot);
                batch.draw();
                tex.unbind();

            }
            void flush(){
                batch.clear();
            }
            const std::array<std::array<float, 8>, count>& getData(){return data;}
            const Texture::Texture& getTexture(){return tex;}

    };
}
