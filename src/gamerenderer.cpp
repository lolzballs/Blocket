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

    m_rotation += glm::vec2(mouseDelta.y, -mouseDelta.x);

    if (m_rotation.x > 90)
    {
        m_rotation.x = 90;
    }
    else if (m_rotation.x < -90)
    {
        m_rotation.x = -90;
    }

    if (input.IsKeyDown(SDLK_w))
    {
        m_movement += glm::vec3(sin(glm::radians(m_rotation.y + 180)), 0,
                                cos(glm::radians(m_rotation.y + 180)));
    }
    if (input.IsKeyDown(SDLK_s))
    {
        m_movement +=
            glm::vec3(sin(glm::radians(m_rotation.y)), 0, cos(glm::radians(m_rotation.y)));
    }
    if (input.IsKeyDown(SDLK_a))
    {
        m_movement += glm::vec3(sin(glm::radians(m_rotation.y - 90)), 0,
                                cos(glm::radians(m_rotation.y - 90)));
    }
    if (input.IsKeyDown(SDLK_d))
    {
        m_movement += glm::vec3(sin(glm::radians(m_rotation.y + 90)), 0,
                                cos(glm::radians(m_rotation.y + 90)));
    }
    if (input.IsKeyDown(SDLK_SPACE))
    {
        m_movement += glm::vec3(0, 1, 0);
    }
    if (input.IsKeyDown(SDLK_LSHIFT))
    {
        m_movement += glm::vec3(0, -1, 0);
    }

    m_world.Input(input);
}

void GameRenderer::Update()
{
    m_world.Update();

    if (m_movement != glm::vec3())
    {
        m_velocity += glm::normalize(m_movement) * 0.5f;
        m_movement = glm::vec3();
    }

    m_position += m_velocity * 0.8f;
    m_velocity *= 0.8f;
}

void GameRenderer::Render(float delta)
{
    glm::vec2 rotation = glm::radians(m_rotation);
    m_transformation = glm::translate(glm::eulerAngleXY(rotation.x, rotation.y),
                                      -(m_position + m_velocity * 0.8f * delta));
    m_shader.UpdateUniforms(m_perspective * m_transformation);

    m_world.Render();
}
