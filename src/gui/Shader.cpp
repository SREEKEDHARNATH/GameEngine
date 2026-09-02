#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "gl.h"
#include "qualifier.hpp"
#include <glm/glm.hpp>

namespace Shader {

    void readFile(const char* path, std::string& source){

        std::ifstream file(path);
        if (!file.is_open()){
            source="";
            std::cout << "Cant open " << path << "\n";
            return;
        }

        std::ostringstream stream;
        stream << file.rdbuf();

        source = stream.str();
    }

    void compileShader(unsigned int type, std::string& source, unsigned int& id){
        id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, NULL);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success){
            char infoLog[512];
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::"
                << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                << "::COMPILATION_FAILED\n" << infoLog << std::endl;
            glDeleteShader(id);
            id =  0;
        }
    }

    void makeShader(const char* vPath, const char* fPath, unsigned int& id){
        std::string vSrc;
        readFile(vPath, vSrc);

        std::string fSrc;
        readFile(fPath, fSrc);

        unsigned int vs,fs;
        compileShader(GL_VERTEX_SHADER, vSrc, vs);
        compileShader(GL_FRAGMENT_SHADER, fSrc, fs);

        if (vs == 0 || fs == 0) {
            std::cerr << "ERROR::SHADER::Program creation aborted due to compilation errors.\n";
            if (vs != 0) glDeleteShader(vs);
            if (fs != 0) glDeleteShader(fs);
            id = 0;
            return;
        }

        id = glCreateProgram();
        glAttachShader(id, vs);
        glAttachShader(id, fs);

        glLinkProgram(id);

        glDeleteShader(vs);
        glDeleteShader(fs);

        int success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success){
            char infoLog[512];
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER-PROGRAM::" << "::LINKING_FAILED\n" << infoLog << std::endl;
            glDeleteProgram(id);
            id =  0;
        }

    }
    void shader::create(const char* vPath, const char* fPath){
        makeShader(vPath, fPath, id);

    }

    void shader::bind(){
        glUseProgram(id);
    }

    void shader::unbind(){
        glUseProgram(0);
    }

    void shader::destroy() {
        unbind();
        glDeleteProgram(id);
        id=0;
    }

    int shader::getLoc(const char* name){

        if (locCache.contains(name)){
            return locCache[name];
        }

        int loc = glGetUniformLocation(id, name);
        if (loc == -1) std::cout << "Warning cant find " << name << "\n";
        locCache[name] = loc;
        return loc;
    }

    void shader::uploadInt(const char* name, int val){
        glUniform1i(getLoc(name), val);
    }

    void shader::uploadFloat(const char* name, float val){
        glUniform1f(getLoc(name), val);
    }

    void shader::uploadDouble(const char* name, double val){
        glUniform1d(getLoc(name), val);
    }


    void shader::uploadVec2f(const char* name, glm::vec<2, float> vec2){
        glUniform2f(getLoc(name), vec2.x, vec2.y);
    }

    void shader::uploadVec3f(const char* name, glm::vec<3, float> vec2){
        glUniform3f(getLoc(name), vec2.x, vec2.y, vec2.z);
    }

    void shader::uploadVec4f(const char* name, glm::vec<4, float> vec2){
        glUniform4f(getLoc(name), vec2.x, vec2.y, vec2.z, vec2.w);
    }


    void shader::uploadVec2i(const char* name, glm::vec<2, int> vec2){
        glUniform2i(getLoc(name), vec2.x, vec2.y);
    }

    void shader::uploadVec3i(const char* name, glm::vec<3, int> vec2){
        glUniform3i(getLoc(name), vec2.x, vec2.y, vec2.z);
    }

    void shader::uploadVec4i(const char* name, glm::vec<4, int> vec2){
        glUniform4i(getLoc(name), vec2.x, vec2.y, vec2.z, vec2.w);
    }


    void shader::uploadVec2d(const char* name, glm::vec<2, double> vec2){
        glUniform2d(getLoc(name), vec2.x, vec2.y);
    }

    void shader::uploadVec3d(const char* name, glm::vec<3, double> vec2){
        glUniform3d(getLoc(name), vec2.x, vec2.y, vec2.z);
    }

    void shader::uploadVec4d(const char* name, glm::vec<4, double> vec2){
        glUniform4d(getLoc(name), vec2.x, vec2.y, vec2.z, vec2.w);
    }


    void shader::uploadMat2f(const char* name, glm::mat<2, 2, float> mat2){
        glUniformMatrix2fv(getLoc(name), 1, GL_FALSE, &mat2[0][0]);
    }

    void shader::uploadMat3f(const char* name, glm::mat<3, 3, float> mat3){
        glUniformMatrix3fv(getLoc(name), 1, GL_FALSE, &mat3[0][0]);
    }

    void shader::uploadMat4f(const char* name, glm::mat<4, 4, float> mat4){
        glUniformMatrix4fv(getLoc(name), 1, GL_FALSE, &mat4[0][0]);
    }

}
