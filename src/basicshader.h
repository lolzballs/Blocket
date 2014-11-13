#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "shader.h"

class BasicShader
	: Shader
{
public:
	BasicShader();
	void UpdateUniforms(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix);
private:
	int m_uniformTransformation;
	int m_uniformColor;
};

#endif
