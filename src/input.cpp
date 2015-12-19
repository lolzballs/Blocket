#include "input.h"

#include <iostream>

void InputHandler::HandleMousePosition(double x, double y)
{
	m_mousePosition = { x, y };
}

void InputHandler::HandleMouseButton(int key, int action, int mods)
{
	m_buttons[key] = action == GLFW_PRESS;
}

void InputHandler::HandleMouseWheel(double xOffset, double yOffset)
{
	m_mouseScroll += glm::vec2(xOffset, yOffset);
	if (m_mouseScroll.x > 0 || m_mouseScroll.y > 0)
	{
		m_mouseScroll = { 0, 0 };
	}
}

void InputHandler::HandleKey(int key, int scancode, int action, int mods)
{
    m_keys[key] = action;
}

bool InputHandler::IsKeyDown(int key)
{
    return m_keys[key];
}

bool InputHandler::IsMouseButtonDown(int button)
{
    return m_buttons[button];
}
