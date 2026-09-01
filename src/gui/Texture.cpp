#include "Texture.h"
#include "stb_image.h"
#include "gl.h"

namespace Texture {

    void Texture::create(const char* filePath){
        int w,h,BPP;
        unsigned char* localbuffer = nullptr;

        stbi_set_flip_vertically_on_load(1);
        localbuffer = stbi_load(filePath, &w, &h, &BPP, 4);

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, localbuffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        if (localbuffer){
            stbi_image_free(localbuffer);
        }

    }

    void Texture::bind(int texSlot){
        glActiveTexture(GL_TEXTURE0 + texSlot);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::unbind(){
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::destroy(){
        unbind();
        glDeleteTextures(1, &id);
        id=0;
    }


}
