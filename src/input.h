#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <map>
#include <iostream>

class InputHandler
{
public:
	static InputHandler& GetInstance()
	{
		static InputHandler instance;
		return instance;
	};

	static void MousePositionCallback(GLFWwindow* window, double x, double y)
	{
		GetInstance().HandleMousePosition(x, y);
	};

	static void MouseButtonCallback(GLFWwindow* window, int key, int action, int mods)
	{
		GetInstance().HandleMouseButton(key, action, mods);
	};

	static void MouseWheelCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		GetInstance().HandleMouseWheel(xOffset, yOffset);
	};

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		GetInstance().HandleKey(key, scancode, action, mods);
	};

	void HandleMousePosition(double x, double y);
	void HandleMouseButton(int key, int action, int mods);
    void HandleMouseWheel(double xOffset, double yOffset);
    void HandleKey(int key, int scancode, int action, int mods);
    bool IsKeyDown(int key);
    bool IsMouseButtonDown(int button);

	inline glm::vec2 GetMouseDelta()
	{
		glm::vec2 delta = m_mousePosition - m_oldMousePosition;
		m_oldMousePosition = m_mousePosition;
		return delta;
	};

    inline glm::vec2 GetMousePosition() const
    {
		return m_mousePosition;
    };

    inline glm::vec2 GetMouseScroll() const
    {
        return -m_mouseScroll;
	};

private:
	InputHandler() {};
	InputHandler(InputHandler const&);
	void operator=(InputHandler const&);

    std::map<int, bool> m_keys;
    std::map<int, int> m_buttons;
	glm::vec2 m_oldMousePosition;
	glm::vec2 m_mousePosition;
    glm::vec2 m_mouseScroll;
};

#endif
