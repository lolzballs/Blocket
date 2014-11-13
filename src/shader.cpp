#include "shader.h"

Shader::Shader(std::string location)
	: m_vertSource(LoadShaderFromFile(location + ".vs")), m_fragSource(LoadShaderFromFile(location + ".fs")),
	m_vertShader(glCreateShader(GL_VERTEX_SHADER_ARB)), m_fragShader(glCreateShader(GL_FRAGMENT_SHADER_ARB)),
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

	glAttachShader(m_program, m_vertShader);
	glAttachShader(m_program, m_fragShader);

	GLint status;
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	std::cout << "Finished loading shader: " << location << " with status: " << status << std::endl;

	if (status == 0)
	{
		GLint length;
		char *info;
		glGetObjectParameterivARB(m_program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
		info = SDL_stack_alloc(char, length++);
		glGetInfoLogARB(m_program, length, NULL, info);

		std::cout << info << std::endl;
	}

	glValidateProgram(m_program);
	glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status);
	std::cout << "Shader " << location << "compiled with validation: " << status << std::endl;
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
		std::cout << "Shader " << file << ": " << stuff << std::endl;
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
	glGetObjectParameterivARB(shader, GL_OBJECT_COMPILE_STATUS_ARB, &status);

	if (status == 0)
	{
		GLint length;
		char *info;

		glGetObjectParameterivARB(shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
		info = SDL_stack_alloc(char, length++);
		glGetInfoLogARB(shader, length, NULL, info);
		std::cerr << "Failed to compile shader: " << info << std::endl;
		SDL_stack_free(info);

		return false;
	}

	return true;
}
