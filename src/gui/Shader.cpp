#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "gl.h"

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
}
