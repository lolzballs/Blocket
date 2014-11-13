#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <map>

class InputHandler
{
public:
	void HandleMouseMotion(SDL_MouseMotionEvent event);
	void HandleMouseButton(SDL_MouseButtonEvent event);
	void HandleMouseWheel(SDL_MouseWheelEvent event);
	void HandleKey(SDL_KeyboardEvent event);
	bool IsKeyDown(int key);
	bool IsMouseButtonDown(int button);

	inline glm::vec2 GetMousePosition() { return m_mousePosition; }
	inline glm::vec2 GetMouseScroll() { return -m_mouseScroll; }
private:
	std::map<int, bool> m_keys;
	std::map<int, bool> m_buttons;
	glm::vec2 m_mousePosition;
	glm::vec2 m_mouseScroll;
};

#endif

