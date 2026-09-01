namespace Texture {
    class Texture{
        unsigned int id;
    public:

        void create(const char* filePath);
        void bind(int texSlot=0);
        void unbind();
        void destroy();
    };
}
