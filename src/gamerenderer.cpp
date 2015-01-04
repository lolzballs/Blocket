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
        m_position -= glm::vec3(0, 0, 0.05);
    }
    if (input.IsKeyDown(SDLK_w)) {
        m_position += glm::vec3(0, 0, 0.05);
    }
    if (input.IsKeyDown(SDLK_a)) {
        m_position += glm::vec3(0.05, 0, 0);
    }
    if (input.IsKeyDown(SDLK_d)) {
        m_position -= glm::vec3(0.05, 0, 0);
    }
    if (input.IsKeyDown(SDLK_SPACE)) {
        m_position += glm::vec3(0, 0.05, 0);
    }

	m_world.Input(input);
}

void GameRenderer::Update(float delta)
{
	m_world.Update(delta);
    m_transformation = glm::translate(glm::mat4(), m_position);
}

void GameRenderer::Render()
{
    m_shader.UpdateUniforms(m_perspective * m_transformation);
    m_world.Render();
}

