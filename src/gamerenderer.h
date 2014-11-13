#include "world.h"
#include "basicshader.h"

class GameRenderer
{
public:
	GameRenderer();
	virtual ~GameRenderer();

	void Input(InputHandler input);
	void Update(float delta);
	void Render();

	inline const World GetWorld() { return m_world; }
private:
	BasicShader m_shader;
	World m_world;
};
