#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "shader.h"

class BasicShader
        : Shader {
public:
    BasicShader();

    void UpdateUniforms(glm::mat4);

private:
    int m_uniformTransformation;
};

#endif
