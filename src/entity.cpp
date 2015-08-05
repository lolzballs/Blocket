#include "entity.h"
#include "util/cside.h"

Entity::Entity(World& world, AABB aabb, glm::vec2 rotation, float speed)
    : m_world(world),
      m_aabb(aabb),
      m_oldposition(aabb.GetPosition()),
      m_position(aabb.GetPosition()),
      m_oldrotation(rotation),
      m_rotation(rotation),
      m_speed(speed)
{
}

Entity::~Entity()
{
}

void Entity::Move(glm::vec3 movement)
{
    if (movement.y > 0 && m_onground)
    {
        m_velocity.y = 0.5;
    }

    if (m_onground)
    {
        m_velocity += movement * m_speed;
        m_velocity *= 0.7f;
    }
    else
    {
        m_velocity += movement * m_speed * 0.25f;
        m_velocity *= 0.95;;
    }

    m_onground = false;

    AABB expanded = m_aabb.Expand(m_velocity);
    std::vector<CollisionSide> sides;
    glm::vec3 center = m_aabb.GetCenter();
    std::vector<AABB> intersecting = m_world.GetIntersectingAABBs(expanded);

    for (auto aabb : intersecting)
    {
        glm::vec3 min = aabb.GetAbsMin();
        glm::vec3 max = aabb.GetAbsMax();

        float minX = min.x;
        float minY = min.y;
        float minZ = min.z;

        float maxX = max.x;
        float maxY = max.y;
        float maxZ = max.z;

        if (m_velocity.y > 0)
        {
            sides.push_back(CollisionSide(
                Geom::Quad3{
                    glm::vec3(minX, minY, minZ), glm::vec3(minX, minY, maxZ),
                    glm::vec3(maxX, minY, maxZ), glm::vec3(maxX, minY, minZ)},
                aabb, center, CSide::YP));
        }
        if (m_velocity.y < 0)
        {
            sides.push_back(CollisionSide(
                Geom::Quad3{
                    glm::vec3(minX, maxY, minZ), glm::vec3(minX, maxY, maxZ),
                    glm::vec3(maxX, maxY, maxZ), glm::vec3(maxX, maxY, minZ)},
                aabb, center, CSide::YN));
        }
        if (m_velocity.x > 0)
        {
            sides.push_back(CollisionSide(
                Geom::Quad3{
                    glm::vec3(minX, maxY, maxZ), glm::vec3(minX, maxY, minZ),
                    glm::vec3(minX, minY, minZ), glm::vec3(minX, minY, maxZ)},
                aabb, center, CSide::XP));
        }
        if (m_velocity.x < 0)
        {
            sides.push_back(CollisionSide(
                Geom::Quad3{
                    glm::vec3(maxX, maxY, maxZ), glm::vec3(maxX, maxY, minZ),
                    glm::vec3(maxX, minY, minZ), glm::vec3(maxX, minY, maxZ)},
                aabb, center, CSide::XN));
        }
        if (m_velocity.z > 0)
        {
            sides.push_back(CollisionSide(
                Geom::Quad3{
                    glm::vec3(minX, minY, minZ), glm::vec3(minX, maxY, minZ),
                    glm::vec3(maxX, maxY, minZ), glm::vec3(maxX, minY, minZ)},
                aabb, center, CSide::ZP));
        }
        if (m_velocity.z < 0)
        {
            sides.push_back(CollisionSide(
                Geom::Quad3{
                    glm::vec3(minX, minY, maxZ), glm::vec3(minX, maxY, maxZ),
                    glm::vec3(maxX, maxY, maxZ), glm::vec3(maxX, minY, maxZ)},
                aabb, center, CSide::ZN));
        }
    }

    std::sort(sides.begin(), sides.end(), CSideCompare());

    bool xCollide = false;
    bool yCollide = false;
    bool zCollide = false;

    float block = 0.0001;

    while (!sides.empty())
    {
        CollisionSide side = sides.front();
        sides.erase(sides.begin());

        if (side.GetType() == CSide::XP && !xCollide)
        {
            if (AABB::IntersectX(
                    Geom::Quad3{
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMax().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMin().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMin().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMax().z)},
                    side.GetQStat(), m_velocity))
            {
                xCollide = true;
                m_position.x =
                    side.GetAABB().GetAbsMin().x - m_aabb.GetMax().x - block;
                m_velocity.x = 0;
            }
        }
        else if (side.GetType() == CSide::XN && !xCollide)
        {
            if (AABB::IntersectX(
                    Geom::Quad3{
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMax().z),
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMin().z),
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMin().z),
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMax().z)},
                    side.GetQStat(), m_velocity))
            {
                xCollide = true;
                m_position.x =
                    side.GetAABB().GetAbsMax().x - m_aabb.GetMin().x + block;
                m_velocity.x = 0;
            }
        }
        else if (side.GetType() == CSide::YP && !yCollide)
        {
            if (AABB::IntersectY(
                    Geom::Quad3{
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMin().z),
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMax().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMax().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMin().z)},
                    side.GetQStat(), m_velocity))
            {
                yCollide = true;
                m_position.y =
                    side.GetAABB().GetAbsMin().y - m_aabb.GetMax().y - block;
                m_velocity.y = 0;
            }
        }
        else if (side.GetType() == CSide::YN && !yCollide)
        {
            if (AABB::IntersectY(
                    Geom::Quad3{
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMin().z),
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMax().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMax().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMin().z)},
                    side.GetQStat(), m_velocity))
            {
                yCollide = true;
                m_position.y =
                    side.GetAABB().GetAbsMax().y - m_aabb.GetMin().y + block;
                m_velocity.y = 0;

                m_onground = true;
            }
        }
        else if (side.GetType() == CSide::ZP && !zCollide)
        {
            if (AABB::IntersectZ(
                    Geom::Quad3{
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMax().z),
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMax().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMax().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMax().z)},
                    side.GetQStat(), m_velocity))
            {
                zCollide = true;
                m_position.z =
                    side.GetAABB().GetAbsMin().z - m_aabb.GetMax().z - block;
                m_velocity.z = 0;
            }
        }
        else if (side.GetType() == CSide::ZN && !zCollide)
        {
            if (AABB::IntersectZ(
                    Geom::Quad3{
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMin().z),
                        glm::vec3(m_aabb.GetAbsMin().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMin().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMax().y,
                                  m_aabb.GetAbsMin().z),
                        glm::vec3(m_aabb.GetAbsMax().x, m_aabb.GetAbsMin().y,
                                  m_aabb.GetAbsMin().z)},
                    side.GetQStat(), m_velocity))
            {
                zCollide = true;
                m_position.z =
                    side.GetAABB().GetAbsMax().z - m_aabb.GetMin().z + block;
                m_velocity.z = 0;
            }
        }
        m_aabb.SetPosition(m_position);
    }

    m_position += m_velocity;
    m_aabb.SetPosition(m_position);
   
    m_velocity.y -= 0.05f;
}
