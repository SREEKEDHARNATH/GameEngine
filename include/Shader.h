namespace Shader {
    class shader{
        private:
            unsigned int id;
        public:
            void create(const char* vPath, const char* fPath);
            void bind();
            void unbind();
            void destroy();

    };
}
