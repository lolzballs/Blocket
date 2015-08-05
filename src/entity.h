#ifndef ENTITY_H
#define ENTITY_H

#include "util/aabb.h"
#include "util/util.h"
#include "world/world.h"

class Entity
{
public:
    Entity(World& world, AABB aabb, glm::vec2 rotation, float speed);
    ~Entity();

    virtual void Update(InputHandler input) = 0;
    virtual void Render(float delta) = 0;

    void Move(glm::vec3 movement);

    inline glm::vec3 GetPosition()
    {
        return m_position;
    }

    inline glm::vec2 GetRotation()
    {
        return m_rotation;
    }

    inline bool IsOnGround()
    {
        return m_onground;
    }

    inline glm::vec3 GetRenderPosition(float delta)
    {
        return Util::Vector::Lerp(m_oldposition, m_position, delta);
    }

    inline glm::vec2 GetRenderRotation(float delta)
    {
        return glm::radians(
            Util::Vector::Lerp(m_oldrotation, m_rotation, delta));
    }

protected:
    World& m_world;
    AABB m_aabb;
    glm::vec3 m_oldposition;
    glm::vec3 m_position;
    glm::vec2 m_oldrotation;
    glm::vec2 m_rotation;
    glm::vec3 m_velocity;
    float m_speed;
    bool m_onground;
};

#endif
