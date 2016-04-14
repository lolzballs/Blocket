#include "window.h"

#include <glad/glad.h>

#include <iostream>

Window::Window(int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_isCloseRequested(false)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (m_window == nullptr)
    {
        std::cerr << "Failed to create window and OpenGL context: " << std::endl;
        return;
    }

	glfwMakeContextCurrent(m_window);

    InitGL();
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
}

void Window::Update()
{
    SwapBuffers();
}

void Window::InitGL()
{
	gladLoadGL();
	std::cerr << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
    glViewport(0, 0, m_width, m_height);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
	glfwPollEvents();
}
