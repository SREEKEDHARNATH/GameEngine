#pragma once
#include "gl.h"
#include <cstddef>
#include <iostream>
namespace Framebuffer{
    class Framebuffer{
        private:
            unsigned int id;
            unsigned int rbo;
            unsigned int type;
            unsigned int texId;
        public:
            void create(int width, int height);

            void bind(unsigned int t=GL_FRAMEBUFFER);
            void unbind();
            unsigned int getId() const noexcept;
            unsigned int getRbo() const noexcept;
            unsigned int getType() const noexcept;
            unsigned int getTexId() const noexcept;

            void destroy();
    };
}
