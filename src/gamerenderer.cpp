#include "gamerenderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

GameRenderer::GameRenderer(float fov, float aspect, float zNear, float zFar)
    : m_player(Player(m_world, glm::vec3(0, 10, 0), glm::vec2(), 0.05f)),
      m_perspective(glm::perspective(glm::radians(fov), aspect, zNear, zFar))
{
}

GameRenderer::~GameRenderer()
{
}

void GameRenderer::Update(InputHandler& input)
{
    m_player.Update(input);
    m_world.Update(input);
}

void GameRenderer::Render(float delta)
{
    glm::vec2 rotation = m_player.GetRenderRotation(delta);
    m_transformation = glm::translate(glm::eulerAngleXY(rotation.x, rotation.y),
                                      -(m_player.GetPlayerRenderPosition(delta)));
    m_shader.UpdateUniforms(m_perspective * m_transformation);

    m_world.Render(m_shader);
    m_player.Render(delta);
}
