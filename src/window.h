#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

class Window
{
public:
    Window(int width, int height, const std::string& title);
    virtual ~Window();

    void Update();

    inline bool IsCloseRequested() const
    {
        return glfwWindowShouldClose(m_window);
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
        return float(m_width) / float(m_height);
    }

    inline const std::string& GetTitle() const
    {
        return m_title;
    }

    inline glm::vec2 GetCenter() const
    {
        return glm::vec2((float)m_width / 2.0f, (float)m_height / 2.0f);
    }

	inline GLFWwindow* GetGLFWWindow() const
    {
		return m_window;
    }

private:
    int m_width;
    int m_height;
    bool m_isCloseRequested;
    std::string m_title;
    GLFWwindow* m_window;

    void InitGL();
    void SwapBuffers();
};

#endif
