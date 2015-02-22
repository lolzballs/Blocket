#ifndef SHADER_H
#define SHADER_H

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader {
public:
    Shader(std::string location);

    virtual ~Shader();

    virtual void UpdateUniforms(glm::mat4 projectionMatrix) = 0;

    inline void Enable() {
        glUseProgram(m_program);
    }

protected:
    std::string m_vertSource;
    std::string m_fragSource;
    GLhandleARB m_vertShader;
    GLhandleARB m_fragShader;
    GLhandleARB m_program;

    inline GLint GetUniform(std::string name) {
        return glGetUniformLocation(m_program, name.c_str());
    }

    inline void BindAttrib(GLuint id, std::string name) {
        glBindAttribLocation(m_program, id, name.c_str());
    }

private:
    std::string LoadShaderFromFile(std::string file);

    bool CompileShader(GLhandleARB shader, std::string source);
};

#endif
