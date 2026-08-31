#include "VBLayout.h"

VBLayout::VBLayout(){init();}
VBLayout::~VBLayout(){destroy();}
void VBLayout::destroy(){
    stride=0;
    elements.clear();
}
void VBLayout::init(){stride=0;elements.clear();}
