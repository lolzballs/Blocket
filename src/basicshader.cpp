#include "basicshader.h"

BasicShader::BasicShader()
	: Shader("res/shaders/viewVertex"), m_uniformTransformation(GetUniform("transformation"))
{

}

void BasicShader::UpdateUniforms(glm::mat4 projectionMatrix)
{
	Enable();

    glUniformMatrix4fv(m_uniformTransformation, 1, GL_FALSE, &projectionMatrix[0][0]);
}
