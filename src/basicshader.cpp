#include "basicshader.h"

BasicShader::BasicShader()
	: Shader("res/shaders/viewVertex"), m_uniformTransformation(GetUniform("transformation"))
{

}

void BasicShader::UpdateUniforms(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix)
{
	Enable();

	glm::mat4 finalMatrix = projectionMatrix * modelViewMatrix;
	glUniformMatrix4fv(m_uniformTransformation, 1, GL_FALSE, &finalMatrix[0][0]);
}