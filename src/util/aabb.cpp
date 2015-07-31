#include "aabb.h"

AABB::AABB(glm::vec3 position, glm::vec3 min, glm::vec3 max)
    : m_position(position)
{
    m_min = position + min;
    m_max = position + max;
}

AABB::~AABB()
{
}

bool AABB::Intersects(AABB other)
{
    double minX = std::max(m_min.x, other.m_min.x);
    double minY = std::max(m_min.y, other.m_min.y);
    double minZ = std::max(m_min.z, other.m_min.z);
    double maxX = std::min(m_max.x, other.m_max.x);
    double maxY = std::min(m_max.y, other.m_max.y);
    double maxZ = std::min(m_max.z, other.m_max.z);
    return !(minX > maxX || minY > maxY || minZ > maxZ);
}

bool AABB::Contains(glm::vec2 point, glm::vec2 points[4])
{
    int j = 3;
    bool oddNodes = false;
    for (unsigned int i = 0; i < 4; j = i++)
    {
        if ((((points[i].y <= point.y) && (point.y < points[j].y)) ||
             ((points[j].y <= point.y) && (point.y < points[i].y))) &&
            (point.x < (points[j].x - points[i].x) * (point.y - points[i].y) /
                               (points[j].y - points[i].y) +
                           points[i].x))
        {
            oddNodes = !oddNodes;
        }
    }
    return oddNodes;
}

AABB AABB::Expand(glm::vec3 amount)
{
    glm::vec3 min = m_min + glm::min(amount, glm::vec3());
    glm::vec3 max = m_max + glm::max(amount, glm::vec3());
    return AABB(m_position, min, max);
}

bool AABB::Intersects(Geom::Quad2 quad, Geom::Line2 line)
{
    if (Geom::Line2::Intersects(quad.a, quad.b, line.start, line.end))
    {
        return true;
    }
    if (Geom::Line2::Intersects(quad.b, quad.c, line.start, line.end))
    {
        return true;
    }
    if (Geom::Line2::Intersects(quad.c, quad.d, line.start, line.end))
    {
        return true;
    }
    if (Geom::Line2::Intersects(quad.d, quad.a, line.start, line.end))
    {
        return true;
    }
    glm::vec2 points[4] = {quad.a, quad.b, quad.c, quad.d};
    if (Contains(line.start, points))
    {
        return true;
    }
    if (Contains(line.end, points))
    {
        return true;
    }
    return false;
}

bool AABB::IntersectX(Geom::Quad3 quad, Geom::Quad3 qSta, glm::vec3 velocity)
{
    Geom::Quad2 q1 = {Geom::Point3FlattenY(quad.a),
                      Geom::Point3FlattenY(quad.b),
                      Geom::Point3FlattenY(quad.b + velocity),
                      Geom::Point3FlattenY(quad.a + velocity)};
    Geom::Quad2 q2 = {Geom::Point3FlattenZ(quad.b),
                      Geom::Point3FlattenZ(quad.c),
                      Geom::Point3FlattenZ(quad.c + velocity),
                      Geom::Point3FlattenZ(quad.b + velocity)};
    Geom::Line2 l1 = {Geom::Point3FlattenY(qSta.a),
                      Geom::Point3FlattenY(qSta.b)};
    Geom::Line2 l2 = {Geom::Point3FlattenZ(qSta.b),
                      Geom::Point3FlattenZ(qSta.c)};
    return Intersects(q1, l1) && Intersects(q2, l2);
}

bool AABB::IntersectX(Geom::Quad3 quad, Geom::Line3 line)
{
    Geom::Line2 q1 = {Geom::Point3FlattenY(quad.a),
                      Geom::Point3FlattenY(quad.b)};
    Geom::Line2 q2 = {Geom::Point3FlattenZ(quad.b),
                      Geom::Point3FlattenZ(quad.c)};
    Geom::Line2 l1 = line.FlattenY();
    Geom::Line2 l2 = line.FlattenZ();
    return Geom::Line2::Intersects(q1, l1) && Geom::Line2::Intersects(q2, l2);
}

bool AABB::IntersectY(Geom::Quad3 quad, Geom::Quad3 qSta, glm::vec3 velocity)
{
    Geom::Quad2 q1 = {Geom::Point3FlattenX(quad.a),
                      Geom::Point3FlattenX(quad.b),
                      Geom::Point3FlattenX(quad.b + velocity),
                      Geom::Point3FlattenX(quad.a + velocity)};
    Geom::Quad2 q2 = {Geom::Point3FlattenZ(quad.b),
                      Geom::Point3FlattenZ(quad.c),
                      Geom::Point3FlattenZ(quad.c + velocity),
                      Geom::Point3FlattenZ(quad.b + velocity)};
    Geom::Line2 l1 = {Geom::Point3FlattenX(qSta.a),
                      Geom::Point3FlattenX(qSta.b)};
    Geom::Line2 l2 = {Geom::Point3FlattenZ(qSta.b),
                      Geom::Point3FlattenZ(qSta.c)};
    return Intersects(q1, l1) && Intersects(q2, l2);
}

bool AABB::IntersectY(Geom::Quad3 quad, Geom::Line3 line)
{
    Geom::Line2 q1 = {Geom::Point3FlattenX(quad.a),
                      Geom::Point3FlattenX(quad.b)};
    Geom::Line2 q2 = {Geom::Point3FlattenZ(quad.b),
                      Geom::Point3FlattenZ(quad.c)};
    Geom::Line2 l1 = line.FlattenX();
    Geom::Line2 l2 = line.FlattenZ();
    return Geom::Line2::Intersects(q1, l1) && Geom::Line2::Intersects(q2, l2);
}

bool AABB::IntersectZ(Geom::Quad3 quad, Geom::Quad3 qSta, glm::vec3 velocity)
{
    Geom::Quad2 q1 = {Geom::Point3FlattenX(quad.a), Geom::Point3FlattenX(quad.b),
                Geom::Point3FlattenX(quad.b + velocity),
                Geom::Point3FlattenX(quad.a + velocity)};
    Geom::Quad2 q2 = {Geom::Point3FlattenY(quad.b), Geom::Point3FlattenY(quad.c),
                Geom::Point3FlattenY(quad.c + velocity),
                Geom::Point3FlattenY(quad.b + velocity)};
    Geom::Line2 l1 = {Geom::Point3FlattenX(qSta.a), Geom::Point3FlattenX(qSta.b)};
    Geom::Line2 l2 = {Geom::Point3FlattenY(qSta.b), Geom::Point3FlattenY(qSta.c)};
    return Intersects(q1, l1) && Intersects(q2, l2);
}

bool AABB::IntersectZ(Geom::Quad3 quad, Geom::Line3 line)
{
    Geom::Line2 q1 = {Geom::Point3FlattenX(quad.a), Geom::Point3FlattenX(quad.b)};
    Geom::Line2 q2 = {Geom::Point3FlattenY(quad.b), Geom::Point3FlattenY(quad.c)};
    Geom::Line2 l1 = line.FlattenX();
    Geom::Line2 l2 = line.FlattenY();
    return Geom::Line2::Intersects(q1, l1) &&
           Geom::Line2::Intersects(q2, l2);
}
