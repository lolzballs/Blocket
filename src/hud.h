#ifndef HUD_H
#define HUD_H

#include "input.h"
#include <GL/glew.h>

class HUD
{
public:
	HUD();
	virtual ~HUD();

	void Input(InputHandler input);
	void Update();
	void Render();
	void InitOrtho(int width, int height, float zNear, float zFar);
private:

};

#endif
