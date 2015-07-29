#include "player.h"

#include "util/util.h"

Player::Player(glm::vec3 position)
    : m_position(position), m_oldposition(position)
{
}

Player::~Player()
{
}

void Player::Input(InputHandler input)
{
    glm::vec2 mouseDelta = input.GetMousePosition();

    m_rotation += glm::vec2(mouseDelta.y, mouseDelta.x);

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
        m_movement += glm::vec3(cos(glm::radians(m_rotation.y - 90)), 0,
                                sin(glm::radians(m_rotation.y - 90)));
    }
    if (input.IsKeyDown(SDLK_s))
    {
        m_movement += glm::vec3(cos(glm::radians(m_rotation.y + 90)), 0,
                                sin(glm::radians(m_rotation.y + 90)));
    }
    if (input.IsKeyDown(SDLK_a))
    {
        m_movement += glm::vec3(cos(glm::radians(m_rotation.y + 180)), 0,
                                sin(glm::radians(m_rotation.y + 180)));
    }
    if (input.IsKeyDown(SDLK_d))
    {
        m_movement += glm::vec3(cos(glm::radians(m_rotation.y)), 0,
                                sin(glm::radians(m_rotation.y)));
    }
    if (input.IsKeyDown(SDLK_SPACE))
    {
        m_movement += glm::vec3(0, 1, 0);
    }
    if (input.IsKeyDown(SDLK_LSHIFT))
    {
        m_movement += glm::vec3(0, -1, 0);
    }
}

void Player::Update()
{
    m_oldposition = m_position;

    if (m_movement != glm::vec3())
    {
        m_velocity += glm::normalize(m_movement) * 0.5f;
        m_movement = glm::vec3();
    }

    m_velocity *= 0.8f;
    m_position += m_velocity;
}

void Player::Render(float delta)
{
    // TODO: Render player
}

glm::vec3 Player::GetRenderPosition(float delta)
{
    return Util::Vector::Lerp(m_oldposition, m_position, delta);
}

glm::vec2 Player::GetRenderRotation()
{
    return glm::radians(m_rotation);
}
