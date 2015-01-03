#include "gamerenderer.h"

GameRenderer::GameRenderer(float fov, float aspect, float zNear, float zFar)
    : m_perspective(glm::perspective(glm::radians(fov), aspect, zNear, zFar))
{
    glm::vec4 coord = m_perspective * glm::vec4(0.5, 0.5, 0.5, 1);
    std::cout << coord.y << ", " << coord.z << std::endl;
}

GameRenderer::~GameRenderer()
{

}

void GameRenderer::Input(InputHandler input)
{
    if (input.IsKeyDown(SDLK_s)) {
        m_position -= glm::vec3(0, 0, 0.001);
    }
    if (input.IsKeyDown(SDLK_SPACE)) {
        m_position += glm::vec3(0, 0.001, 0);
    }

    m_transformation = glm::translate(m_transformation, m_position);

	m_world.Input(input);
}

void GameRenderer::Update(float delta)
{
	m_world.Update(delta);
}

void GameRenderer::Render()
{
    m_shader.UpdateUniforms(m_perspective * m_transformation);
//	m_shader.UpdateUniforms(m_perspective);
    m_world.Render();
}

