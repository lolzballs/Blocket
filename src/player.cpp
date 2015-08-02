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
      m_world(world),
      m_vbo(0)
{
    InitGL();
}

Player::~Player()
{
    glDeleteBuffers(1, &m_vbo);
}

void Player::InitGL()
{
    glGenBuffers(1, &m_vbo);
}

void Player::BufferBoundingBox(float delta)
{
    AABB last = AABB(m_oldposition, glm::vec3(-0.4, 0, -0.4),
                     glm::vec3(0.4, 1.8, 0.4)).Expand(m_velocity);
    AABB now = m_aabb.Expand(m_velocity);
    glm::vec3 min =
        Util::Vector::Lerp(last.GetAbsMin(), now.GetAbsMin(), delta);
    glm::vec3 size = Util::Vector::Lerp(last.GetSize(), now.GetSize(), delta);
    glm::vec4 color = glm::vec4(1, 1, 1, 1);
    std::array<Vertex, 32> vertices{
        {// back
         Vertex(min, color), Vertex(min + glm::vec3(0, size.y, 0), color),
         Vertex(min + glm::vec3(size.x, size.y, 0), color),
         Vertex(min + glm::vec3(size.x, 0, 0), color),
         // front
         Vertex(min + glm::vec3(0, size.y, size.z), color),
         Vertex(min + glm::vec3(0, 0, size.z), color),
         Vertex(min + glm::vec3(size.x, 0, size.z), color),
         Vertex(min + glm::vec3(size.x, size.y, size.z), color),
         // down
         Vertex(min + glm::vec3(size.x, 0, 0), color),
         Vertex(min + glm::vec3(size.x, 0, size.z), color),
         Vertex(min + glm::vec3(size.x, 0, size.z), color),
         Vertex(min + glm::vec3(0, 0, size.z), color),
         Vertex(min + glm::vec3(0, 0, size.z), color), Vertex(min, color),
         Vertex(min + glm::vec3(size.x, 0, 0), color),
         Vertex(min + glm::vec3(0, 0, 0), color),
         // up
         Vertex(min + glm::vec3(0, size.y, 0), color),
         Vertex(min + glm::vec3(0, size.y, size.z), color),
         Vertex(min + glm::vec3(0, size.y, size.z), color),
         Vertex(min + glm::vec3(size.x, size.y, size.z), color),
         Vertex(min + glm::vec3(size.x, size.y, size.z), color),
         Vertex(min + glm::vec3(size.x, size.y, 0), color),
         Vertex(min + glm::vec3(0, size.y, 0), color),
         Vertex(min + glm::vec3(size.x, size.y, 0), color),
         // left
         Vertex(min + glm::vec3(0, size.y, size.z), color),
         Vertex(min + glm::vec3(0, size.y, 0), color),
         Vertex(min + glm::vec3(0, 0, 0), color),
         Vertex(min + glm::vec3(0, 0, size.z), color),
         // right
         Vertex(min + glm::vec3(size.x, 0, 0), color),
         Vertex(min + glm::vec3(size.x, size.y, 0), color),
         Vertex(min + glm::vec3(size.x, size.y, size.z), color),
         Vertex(min + glm::vec3(size.x, 0, size.z), color)}};

    float* floatVertices =
        Vertex::GetFloatArray(vertices.data(), vertices.size());

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * VERTEX_SIZE * sizeof(float),
                 floatVertices, GL_DYNAMIC_DRAW);
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

    AABB expanded = m_aabb.Expand(m_velocity);
    std::priority_queue<CollisionSide, std::vector<CollisionSide>, CSideCompare>
        sides;
    glm::vec3 center = m_aabb.GetCenter();
    std::vector<AABB> intersecting = m_world->GetIntersectingAABBs(expanded);

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
            sides.push(CollisionSide(Geom::Quad3{glm::vec3(minX, minY, minZ),
                                                 glm::vec3(minX, minY, maxZ),
                                                 glm::vec3(maxX, minY, maxZ),
                                                 glm::vec3(maxX, minY, minZ)},
                                     aabb, center, CSIDE_YP));
        }
        if (m_velocity.y < 0)
        {
            sides.push(CollisionSide(Geom::Quad3{glm::vec3(minX, maxY, minZ),
                                                 glm::vec3(minX, maxY, maxZ),
                                                 glm::vec3(maxX, maxY, maxZ),
                                                 glm::vec3(maxX, maxY, minZ)},
                                     aabb, center, CSIDE_YN));
        }
        if (m_velocity.x > 0)
        {
            sides.push(CollisionSide(Geom::Quad3{glm::vec3(minX, maxY, maxZ),
                                                 glm::vec3(minX, maxY, minZ),
                                                 glm::vec3(minX, minY, minZ),
                                                 glm::vec3(minX, minY, maxZ)},
                                     aabb, center, CSIDE_XP));
        }
        if (m_velocity.x < 0)
        {
            sides.push(CollisionSide(Geom::Quad3{glm::vec3(maxX, maxY, maxZ),
                                                 glm::vec3(maxX, maxY, minZ),
                                                 glm::vec3(maxX, minY, minZ),
                                                 glm::vec3(maxX, minY, maxZ)},
                                     aabb, center, CSIDE_XN));
        }
        if (m_velocity.z > 0)
        {
            sides.push(CollisionSide(Geom::Quad3{glm::vec3(minX, minY, minZ),
                                                 glm::vec3(minX, maxY, minZ),
                                                 glm::vec3(maxX, maxY, minZ),
                                                 glm::vec3(maxX, minY, minZ)},
                                     aabb, center, CSIDE_ZP));
        }
        if (m_velocity.z < 0)
        {
            sides.push(CollisionSide(Geom::Quad3{glm::vec3(minX, minY, maxZ),
                                                 glm::vec3(minX, maxY, maxZ),
                                                 glm::vec3(maxX, maxY, maxZ),
                                                 glm::vec3(maxX, minY, maxZ)},
                                     aabb, center, CSIDE_ZN));
        }
    }

    bool xCollide = false;
    bool yCollide = false;
    bool zCollide = false;

    float block = 0.0001;

    while (!sides.empty())
    {
        CollisionSide side = sides.top();
        sides.pop();
        if (side.GetType() == CSIDE_XP && !xCollide)
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
        else if (side.GetType() == CSIDE_XN && !xCollide)
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
        else if (side.GetType() == CSIDE_YP && !yCollide)
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
        else if (side.GetType() == CSIDE_YN && !yCollide)
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
            }
        }
        else if (side.GetType() == CSIDE_ZP && !zCollide)
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
        else if (side.GetType() == CSIDE_ZN && !zCollide)
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

    // COLLISION CODE END

    m_position += m_velocity;

    m_aabb.SetPosition(m_position);
}

void Player::Render(float delta)
{
    BufferBoundingBox(delta);

    // glDisable(GL_CULL_FACE);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float),
                          (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float),
                          (GLvoid*)12);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float),
                          (GLvoid*)20);

    glDrawArrays(GL_LINES, 0, (GLsizei)24);
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    //    glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

glm::vec3 Player::GetRenderPosition(float delta)
{
    return Util::Vector::Lerp(m_oldposition, m_position, delta) +
           glm::vec3(0, 1.5, 0);
}

glm::vec2 Player::GetRenderRotation(float delta)
{
    return glm::radians(Util::Vector::Lerp(m_oldrotation, m_rotation, delta));
}
