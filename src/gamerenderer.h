#include "world.h"
#include "basicshader.h"

#include <glm/gtc/matrix_transform.hpp>

class GameRenderer
{
public:
    GameRenderer(float fov, float aspect, float zNear, float zFar);
	virtual ~GameRenderer();

	void Input(InputHandler input);
	void Update(float delta);
	void Render();

	inline const World GetWorld() { return m_world; }
private:
	BasicShader m_shader;
	World m_world;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::mat4 m_perspective;
    glm::mat4 m_transformation;
};
