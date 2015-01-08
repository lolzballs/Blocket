#include "window.h"
#include <SDL2/SDL_opengl.h>

Window::Window(int width, int height, const std::string& title)
	: m_width(width), m_height(height), m_isCloseRequested(false)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (m_window == NULL) {
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		return;
	}

	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == NULL) {
		std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
		return;
	}

	InitGL();
}

Window::~Window()
{
	SDL_DestroyWindow(m_window);
}

void Window::SetMousePosition(int x, int y)
{
	SDL_WarpMouseInWindow(m_window, x, y);
}

void Window::Update()
{
	SDL_GL_SetSwapInterval(0);

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			m_isCloseRequested = true;
		}
		else if (event.type == SDL_MOUSEWHEEL)
		{
			m_input.HandleMouseWheel(event.wheel);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
		{
			m_input.HandleMouseButton(event.button);
		}
		else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			m_input.HandleKey(event.key);
		}
	}

	SwapBuffers();
}

void Window::InitGL()
{
	glViewport(0, 0, m_width, m_height);
	glewInit();		
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}
