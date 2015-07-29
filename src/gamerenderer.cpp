#include "gamerenderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

GameRenderer::GameRenderer(float fov, float aspect, float zNear, float zFar)
    : m_player(Player(glm::vec3())),
      m_perspective(glm::perspective(glm::radians(fov), aspect, zNear, zFar))
{
}

GameRenderer::~GameRenderer()
{
}

void GameRenderer::Update(InputHandler input)
{
    m_player.Update(input);
    m_world.Update(input);
}

void GameRenderer::Render(float delta)
{
    glm::vec2 rotation = m_player.GetRenderRotation();
    m_transformation = glm::translate(glm::eulerAngleXY(rotation.x, rotation.y),
                                      -(m_player.GetRenderPosition(delta)));
    m_shader.UpdateUniforms(m_perspective * m_transformation);

    m_world.Render();
}
