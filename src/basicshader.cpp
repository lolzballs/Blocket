#include "basicshader.h"

BasicShader::BasicShader()
        : Shader("res/shaders/viewVertex"), m_uniformTransformation(GetUniform("transform")) {
    BindAttrib(0, "position");
    BindAttrib(1, "texCoord");
    BindAttrib(2, "color");
}

void BasicShader::UpdateUniforms(glm::mat4 projectionMatrix) {
    Enable();

    glUniformMatrix4fv(m_uniformTransformation, 1, GL_FALSE, &projectionMatrix[0][0]);
}
