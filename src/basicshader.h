#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "shader.h"

class BasicShader : public Shader
{
public:
    BasicShader();

    void UpdateUniforms(glm::mat4);

    GLint m_uniformTransformation;
};

#endif
