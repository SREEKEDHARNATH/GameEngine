#include "Renderer.h"
#include "VBLayout.h"
#include "gl.h"

namespace Renderer {
    vertexArray::~vertexArray(){
        destroy();
    }

    vertexArray::vertexArray(){
        init();
    }

    void vertexArray::init(){

        glGenVertexArrays(1, &id);
    }

    void vertexArray::destroy(){
        glDeleteVertexArrays(1, &id);
    }

    void vertexArray::bind(){
        glBindVertexArray(id);
    }

    void vertexArray::unbind(){
        glBindVertexArray(0);
    }




}
