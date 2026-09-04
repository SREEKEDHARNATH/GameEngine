#pragma once

class Component{
    public:
        Component();
        virtual ~Component()=0;
        virtual void Imgui()=0;
        virtual void init()=0;
        virtual void destroy()=0;
        virtual const unsigned long long getId()=0;
};
