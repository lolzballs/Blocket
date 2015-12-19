#include "shader.h"

#include <iostream>
#include <fstream>
#include <memory>

Shader::Shader(std::string location)
    : m_vertSource(LoadShaderFromFile(location + ".vs")),
      m_fragSource(LoadShaderFromFile(location + ".fs")),
      m_vertShader(glCreateShader(GL_VERTEX_SHADER_ARB)),
      m_fragShader(glCreateShader(GL_FRAGMENT_SHADER_ARB)),
      m_program(glCreateProgram())
{
    glGetError();

    if (!CompileShader(m_vertShader, m_vertSource))
    {
        return;
    }

    if (!CompileShader(m_fragShader, m_fragSource))
    {
        return;
    }
}

Shader::~Shader()
{
}

std::string Shader::LoadShaderFromFile(std::string file)
{
    std::string stuff;
    std::ifstream sourceFile(file.c_str());

    std::string line;
    if (sourceFile.is_open())
    {
        while (!sourceFile.eof())
        {
            getline(sourceFile, line);
            stuff = stuff + line + "\n";
        }
    }
    else
    {
        std::cout << "Could not open file " << file << std::endl;
    }

    return stuff;
}

bool Shader::CompileShader(GLhandleARB shader, std::string source)
{
    GLint status;

    const char *sourceChars = source.c_str();

    glShaderSource(shader, 1, &sourceChars, 0);
    glCompileShader(shader);
    glGetObjectParameterivARB(shader, GL_COMPILE_STATUS, &status);

    if (status == 0)
    {
        GLint length;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::unique_ptr<char[]> info(new char[length]);
		glGetShaderInfoLog(shader, length, nullptr, info.get());
        std::cerr << "Failed to compile shader: " << info.get() << std::endl;

        return false;
    }

    return true;
}

bool Shader::LinkShader()
{
	glAttachShader(m_program, m_vertShader);
	glAttachShader(m_program, m_fragShader);
	glDeleteShader(m_vertShader);
	glDeleteShader(m_fragShader);

	GLint status;
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	std::cout << "Finished loading shader with status: " << status << std::endl;

	if (!status)
	{
		GLint length;

		glGetObjectParameterivARB(m_program, GL_INFO_LOG_LENGTH, &length);
		std::unique_ptr<char[]> info(new char[length]);
		glGetInfoLogARB(m_program, length, nullptr, info.get());

		std::cout << info.get() << std::endl;
	}

	glValidateProgram(m_program);
	glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status);
	std::cout << "Shader compiled with validation: " << status
		<< std::endl;

	return status;
}