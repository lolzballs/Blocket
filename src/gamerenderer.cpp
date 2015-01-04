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
    glm::vec2 mouseDelta = input.GetMousePosition();

    if (mouseDelta.y > 90)
    {
        mouseDelta.y = 90;
    }
    else if (mouseDelta.y < -90)
    {
        mouseDelta.y = -90;
    }

    m_rotation += glm::vec2(mouseDelta.y, -mouseDelta.x);

    if (input.IsKeyDown(SDLK_s))
    {
        m_position += glm::vec3(0, 0, 0.05);
    }
    if (input.IsKeyDown(SDLK_w))
    {
        m_position -= glm::vec3(0, 0, 0.05);
    }
    if (input.IsKeyDown(SDLK_a))
    {
        m_position -= glm::vec3(0.05, 0, 0);
    }
    if (input.IsKeyDown(SDLK_d))
    {
        m_position += glm::vec3(0.05, 0, 0);
    }
    if (input.IsKeyDown(SDLK_SPACE))
    {
        m_position += glm::vec3(0, 0.05, 0);
    }

	m_world.Input(input);
}

void GameRenderer::Update(float delta)
{
	m_world.Update(delta);
    glm::vec2 rotation = glm::radians(m_rotation);
    m_transformation = glm::translate(glm::eulerAngleXY(rotation.x, rotation.y), -m_position);
}

void GameRenderer::Render()
{
    m_shader.UpdateUniforms(m_perspective * m_transformation);
    m_world.Render();
}

