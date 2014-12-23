#include "gamerenderer.h"

GameRenderer::GameRenderer(float fov, float aspect, float zNear, float zFar)
    : m_perspective(glm::perspective(glm::radians(fov), aspect, zNear, zFar))
{

}

GameRenderer::~GameRenderer()
{

}

void GameRenderer::Input(InputHandler input)
{
    if (input.IsKeyDown(SDLK_s)) {
        m_position -= glm::vec3(0, 1, 0);
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
	m_world.Render();
}

