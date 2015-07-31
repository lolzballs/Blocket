#include "player.h"
#include "util/util.h"

#include <glm/ext.hpp>

#include <iostream>

Player::Player(glm::vec2 rotation, glm::vec3 position, float speed,
               World* world)
    : m_aabb(
          AABB(position, glm::vec3(-0.4, 0, -0.4), glm::vec3(0.4, 1.8, 0.4))),
      m_rotation(rotation),
      m_oldrotation(rotation),
      m_position(position),
      m_oldposition(position),
      m_speed(speed),
      m_world(world)
{
}

Player::~Player()
{
}

void Player::Update(InputHandler input)
{
    m_oldposition = m_position;
    m_oldrotation = m_rotation;

    glm::vec2 mouseDelta = input.GetMousePosition();
    m_rotation += glm::vec2(mouseDelta.y, mouseDelta.x) * 0.25;

    if (m_rotation.x > 90)
    {
        m_rotation.x = 90;
    }
    else if (m_rotation.x < -90)
    {
        m_rotation.x = -90;
    }

    glm::vec3 movement;
    if (input.IsKeyDown(SDLK_w))
    {
        movement += glm::vec3(cos(glm::radians(m_rotation.y - 90)), 0,
                              sin(glm::radians(m_rotation.y - 90)));
    }
    if (input.IsKeyDown(SDLK_s))
    {
        movement += glm::vec3(cos(glm::radians(m_rotation.y + 90)), 0,
                              sin(glm::radians(m_rotation.y + 90)));
    }
    if (input.IsKeyDown(SDLK_a))
    {
        movement += glm::vec3(cos(glm::radians(m_rotation.y + 180)), 0,
                              sin(glm::radians(m_rotation.y + 180)));
    }
    if (input.IsKeyDown(SDLK_d))
    {
        movement += glm::vec3(cos(glm::radians(m_rotation.y)), 0,
                              sin(glm::radians(m_rotation.y)));
    }
    if (input.IsKeyDown(SDLK_SPACE))
    {
        movement += glm::vec3(0, 1, 0);
    }
    if (input.IsKeyDown(SDLK_LSHIFT))
    {
        movement += glm::vec3(0, -1, 0);
    }

    if (movement != glm::vec3())
    {
        m_velocity += glm::normalize(movement) * m_speed;
        movement = glm::vec3();
    }

    m_velocity *= 0.8f;

    // COLLISION CODE

    glm::vec3 pos = m_aabb.GetMin();
    std::cout << glm::to_string(pos) << std::endl;

    AABB expanded = m_aabb.Expand(m_velocity);
    std::priority_queue<CollisionSide, std::vector<CollisionSide>, CSideCompare>
        queue;
    glm::vec3 center = m_aabb.GetCenter();
    std::vector<AABB> intersecting = m_world->GetIntersectingAABBs(expanded);

    for (std::vector<AABB>::size_type i = 0; i < intersecting.size(); ++i)
    {
    }

    // COLLISION CODE END

    m_position += m_velocity;

    m_aabb.SetPosition(m_position);
}

glm::vec3 Player::GetRenderPosition(float delta)
{
    return Util::Vector::Lerp(m_oldposition, m_position, delta);
}

glm::vec2 Player::GetRenderRotation(float delta)
{
    return glm::radians(Util::Vector::Lerp(m_oldrotation, m_rotation, delta));
}
