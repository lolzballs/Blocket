#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include "input.h"
#include <string>

class Window
{
public:
    Window(const int width, const int height, const std::string title);
    ~Window();
private:
    const int m_width;
    const int m_height;
    const std::string m_title;
    GLFWwindow* m_window;

    void InitGL();
};

#endif // WINDOW_H
