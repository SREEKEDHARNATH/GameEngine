#include "Sprite.h"
#include "Component.h"

Sprite::Sprite(){

}
Sprite::~Sprite(){
    for (Component* component : components){
        component->destroy();
    }
}
void Sprite::Imgui(){
    for (Component* component : components){
        component->Imgui();
    }
}
void Sprite::addComponent(Component* component){
    components.push_back(component);
}
void Sprite::removeComponent(Component* component){
    for (int i=0;i<components.size();i++){
        if (components[i]->getId() == component->getId()){
            components.erase(components.begin()+i);
            return;
        }
    }
}
