#include "gamerenderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

GameRenderer::GameRenderer(float fov, float aspect, float zNear, float zFar)
    : m_player(Player(m_world, glm::vec3(0, 10, 0), glm::vec2(), 0.05f)),
      m_perspective(glm::perspective(glm::radians(fov), aspect, zNear, zFar)),
	  m_spritesheet(Util::Texture::LoadTexture("./res/textures/blocks.png"))
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

	glBindTexture(GL_TEXTURE_2D, m_spritesheet);
    m_world.Render(m_shader);
	glBindTexture(GL_TEXTURE_2D, 0);

    m_player.Render(delta);
}
