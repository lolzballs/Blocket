#include "gamerenderer.h"

GameRenderer::GameRenderer(float fov, float aspect, float zNear, float zFar)
    : m_perspective(glm::perspective(glm::radians(fov), aspect, zNear, zFar))
{
}

GameRenderer::~GameRenderer()
{

}

glm::vec3 movement;

void GameRenderer::Input(InputHandler input)
{
    glm::vec2 mouseDelta = input.GetMousePosition();

    m_rotation += glm::vec2(mouseDelta.y, -mouseDelta.x);

    if (m_rotation.x > 90)
    {
        m_rotation.x = 90;
    }
    else if (m_rotation.x < -90)
    {
        m_rotation.x = -90;
    }

    if (input.IsKeyDown(SDLK_s))
    {
        movement += glm::vec3(0, 0, 1);
    }
    if (input.IsKeyDown(SDLK_w))
    {
        movement -= glm::vec3(0, 0, 1);
    }
    if (input.IsKeyDown(SDLK_a))
    {
        movement -= glm::vec3(1, 0, 0);
    }
    if (input.IsKeyDown(SDLK_d))
    {
        movement += glm::vec3(1, 0, 0);
    }
    if (input.IsKeyDown(SDLK_SPACE))
    {
        movement += glm::vec3(0, 1, 0);
    }

	m_world.Input(input);
}

void GameRenderer::Update()
{
	m_world.Update();

    if (movement != glm::vec3())
    {
        m_velocity += glm::normalize(movement);
        movement = glm::vec3();
    }

    m_position += m_velocity * 0.1f;
    m_velocity *= 0.1f;
}

void GameRenderer::Render()
{

    glm::vec2 rotation = glm::radians(m_rotation);
    m_transformation = glm::translate(glm::eulerAngleXY(rotation.x, rotation.y), -m_position);
    m_shader.UpdateUniforms(m_perspective * m_transformation);
    m_world.Render();
}

