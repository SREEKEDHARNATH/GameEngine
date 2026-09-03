#pragma once

#include "Component.h"
#include <vector>

class Sprite{
    private:
        std::vector<Component*> components;
    public:
        Sprite();
        ~Sprite();
        void Imgui();
        void addComponent(Component* component);
        void removeComponent(Component* component);

};
