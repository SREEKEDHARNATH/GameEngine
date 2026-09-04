#pragma once
#include "qualifier.hpp"
#include <string>
#include <unordered_map>
#include "gl.h"
namespace Shader {
    class shader{
        private:
            unsigned int id;
            mutable std::unordered_map<std::string, int> locCache;
            mutable bool hasInited=false;
        public:

            void create(const char* vPath, const char* fPath);
            void bind() const;
            void unbind() const;
            void destroy();

            int getLoc(const char* name) const;
            void uploadInt(const char* name, int val) const;
            void uploadFloat(const char* name, float val) const;
            void uploadDouble(const char* name, double val) const;

            template<int size>
            void uploadArray(const char* name, int array[size]) const{
                int loc = getLoc(name);
                glUniform1iv(loc, size, array);
            }
            void uploadVec2f(const char* name, glm::vec<2, float> vec2) const;
            void uploadVec3f(const char* name, glm::vec<3, float> vec2) const;
            void uploadVec4f(const char* name, glm::vec<4, float> vec2) const;

            void uploadVec2i(const char* name, glm::vec<2, int> vec2) const;
            void uploadVec3i(const char* name, glm::vec<3, int> vec2) const;
            void uploadVec4i(const char* name, glm::vec<4, int> vec2) const;

            void uploadVec2d(const char* name, glm::vec<2, double> vec2) const;
            void uploadVec3d(const char* name, glm::vec<3, double> vec2) const;
            void uploadVec4d(const char* name, glm::vec<4, double> vec2) const;

            void uploadMat2f(const char* name, glm::mat<2, 2, float> mat2) const;
            void uploadMat3f(const char* name, glm::mat<3, 3, float> mat3) const;
            void uploadMat4f(const char* name, glm::mat<4, 4, float> mat4) const;

    };
}
