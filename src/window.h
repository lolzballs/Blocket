#ifndef WINDOW_H
#define WINDOW_H

#include "input.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>

class Window
{
public:
    Window(int width, int height, const std::string &title);

    virtual ~Window();

    void SetMousePosition(int x, int y);

    void Update();

    inline bool IsCloseRequested() const
    {
        return m_isCloseRequested;
    }

    inline int GetWidth() const
    {
        return m_width;
    }
    inline int GetHeight() const
    {
        return m_height;
    }

    inline float GetAspect() const
    {
        return (float)m_width / (float)m_height;
    }

    inline const std::string &GetTitle() const
    {
        return m_title;
    }

    inline glm::vec2 GetCenter() const
    {
        return glm::vec2((float)m_width / 2.0f, (float)m_height / 2.0f);
    }

    inline InputHandler GetInput()
    {
        return m_input;
    }

private:
    int m_width;
    int m_height;
    bool m_isCloseRequested;
    std::string m_title;
    SDL_Window *m_window;
    SDL_GLContext m_glContext;
    InputHandler m_input;

    void InitGL();
    void SwapBuffers();
};

#endif
