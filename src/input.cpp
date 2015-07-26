#include "input.h"

void InputHandler::HandleMouseButton(SDL_MouseButtonEvent event)
{
    m_buttons[event.button] = event.type == SDL_MOUSEBUTTONDOWN;
}

void InputHandler::HandleMouseWheel(SDL_MouseWheelEvent event)
{
    m_mouseScroll += glm::vec2(event.x, event.y);
    if (m_mouseScroll.x > 0 || m_mouseScroll.y > 0)
    {
        m_mouseScroll = glm::vec2(0, 0);
    }
}

void InputHandler::HandleKey(SDL_KeyboardEvent event)
{
    m_keys[event.keysym.sym] = event.type == SDL_KEYDOWN;
}

bool InputHandler::IsKeyDown(int key)
{
    return m_keys[key];
}

bool InputHandler::IsMouseButtonDown(int button)
{
    return m_buttons[button];
}

glm::vec2 InputHandler::GetMousePosition()
{
    int x, y;
    SDL_GetRelativeMouseState(&x, &y);
    return glm::vec2(x, y);
}
