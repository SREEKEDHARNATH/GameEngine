#pragma once
namespace Texture {
    class Texture{
        unsigned int id=0;
    public:

        void create(const char* filePath);
        void bind(int texSlot=0) const;
        void unbind() const;
        void destroy();
        unsigned int getId() const;
    };
}
