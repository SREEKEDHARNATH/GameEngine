#include "qualifier.hpp"
#include <string>
#include <unordered_map>
namespace Shader {
    class shader{
        private:
            unsigned int id;
            std::unordered_map<std::string, int> locCache;
        public:

            void create(const char* vPath, const char* fPath);
            void bind();
            void unbind();
            void destroy();

            int getLoc(const char* name);
            void uploadInt(const char* name, int val);
            void uploadFloat(const char* name, float val);
            void uploadDouble(const char* name, double val);

            void uploadVec2f(const char* name, glm::vec<2, float> vec2);
            void uploadVec3f(const char* name, glm::vec<3, float> vec2);
            void uploadVec4f(const char* name, glm::vec<4, float> vec2);

            void uploadVec2i(const char* name, glm::vec<2, int> vec2);
            void uploadVec3i(const char* name, glm::vec<3, int> vec2);
            void uploadVec4i(const char* name, glm::vec<4, int> vec2);

            void uploadVec2d(const char* name, glm::vec<2, double> vec2);
            void uploadVec3d(const char* name, glm::vec<3, double> vec2);
            void uploadVec4d(const char* name, glm::vec<4, double> vec2);

            void uploadMat2f(const char* name, glm::mat<2, 2, float> mat2);
            void uploadMat3f(const char* name, glm::mat<3, 3, float> mat3);
            void uploadMat4f(const char* name, glm::mat<4, 4, float> mat4);

    };
}
