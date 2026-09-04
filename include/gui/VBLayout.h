#pragma once
#include <iostream>
#include <vector>
#include "gl.h"

struct VBElement{
    unsigned int type=0;
    unsigned int count=0;
    bool normalised=false;

    static unsigned int getSize(unsigned int type){
        switch (type) {
            case GL_FLOAT : return sizeof(float);
            case GL_UNSIGNED_INT : return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE : return sizeof(char);

        }
        return 0;
    }

};

class VBLayout{
    private:
        unsigned int stride=0;
        std::vector<VBElement> elements;
    public:
        VBLayout();
        ~VBLayout();
        void destroy();
        void init();
        template<typename T>
        void push(unsigned int count){
            std::cout << "Error not supported\n";
        }

        inline const std::vector<VBElement>& getElements() const {
            return elements;
        }
        inline unsigned int getStride() const {return stride;}
};

template<> inline void VBLayout::push<float>(unsigned int count){
    elements.push_back({GL_FLOAT,count, GL_FALSE});
    stride += count * VBElement::getSize(GL_FLOAT);
}

template<> inline void VBLayout::push<unsigned int>(unsigned int count){
    elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    stride += count * VBElement::getSize(GL_UNSIGNED_INT);
}

template<> inline void VBLayout::push<unsigned char>(unsigned int count){
    elements.push_back({GL_UNSIGNED_BYTE,count, GL_TRUE});
    stride += count * VBElement::getSize(GL_UNSIGNED_BYTE);
}
