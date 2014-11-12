#include "window.h"

Window::Window(const int width, const int height, const std::string title)
    : m_width(width), m_height(height), m_title(title)
{
}

Window::~Window()
{

}

void Window::InitGL()
{
    glewInit();
}
