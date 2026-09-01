#include <gl.h>
#include <vector>
#include "VBLayout.h"

namespace Renderer {

    template<typename T> class vertexBuffer {
        private:
            unsigned int id;
        public:
            vertexBuffer(){}

            vertexBuffer(const T* data, unsigned int size, unsigned int drawMethod=GL_STATIC_DRAW){
                init(data, size, drawMethod);
            }

            ~vertexBuffer(){destroy();}

            void init(const T* data, unsigned int size, unsigned int drawMethod=GL_STATIC_DRAW){
                glGenBuffers(1, &id);
                bind();
                glBufferData(GL_ARRAY_BUFFER, size, data, drawMethod);
                unbind();
            }

            void destroy(){
                glDeleteBuffers(1, &id);
            }

            void bind(){
                glBindBuffer(GL_ARRAY_BUFFER, id);
            }

            void unbind(){
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }
    };

    template<typename T> class indexBuffer {
        private:
            unsigned int id;
            int count;
        public:
            indexBuffer(){}

            indexBuffer(const T* data, unsigned int size, unsigned int drawMethod=GL_STATIC_DRAW){
                init(data, size, drawMethod);
            }

            ~indexBuffer(){destroy();}

            void init(const T* data, unsigned int size, unsigned int drawMethod=GL_STATIC_DRAW){
                glGenBuffers(1, &id);
                bind();
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, drawMethod);
                count=size/sizeof(T);
                unbind();
            }
            int getCount(){return count;}

            void destroy(){
                glDeleteBuffers(1, &id);
            }

            void bind(){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
            }

            void unbind(){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
    };

    class vertexArray {
        private:
            unsigned int id;
            unsigned int currentAttributeIndex=0;
        public:
            vertexArray();
            ~vertexArray();

            void init();
            void destroy();

            void bind();
            void unbind();

            template<typename T> void addVbo(vertexBuffer<T>& vbo, VBLayout& vblayout){
                unsigned int offset=0;
                bind();
                vbo.bind();
                const auto& elements = vblayout.getElements();
                for (unsigned int i=0;i<elements.size();i++){
                    const auto& elem = elements[i];
                    glEnableVertexAttribArray(currentAttributeIndex);
                    glVertexAttribPointer(currentAttributeIndex, elem.count, elem.type, elem.normalised ? GL_TRUE : GL_FALSE, vblayout.getStride(), (const void*)(uintptr_t)offset);
                    offset+=elem.count * VBElement::getSize(elem.type);
                    currentAttributeIndex++;
                }
            }
    };
}
