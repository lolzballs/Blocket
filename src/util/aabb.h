#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>
#include <algorithm>

#include "geom.h"

class AABB
{
public:
    AABB(glm::vec3 position, glm::vec3 min, glm::vec3 max);
    ~AABB();

    inline glm::vec3 GetPosition()
    {
        return m_position;
    }

    inline glm::vec3 GetMin()
    {
        return m_min;
    }

    inline glm::vec3 GetMax()
    {
        return m_max;
    }

    inline glm::vec3 GetSize()
    {
        return m_max - m_min;
    }

    inline glm::vec3 GetCenter()
    {
        return (m_min + m_max) / 2.0f;
    }

    bool Intersects(AABB other);

    static bool Contains(glm::vec2 point, glm::vec2 points[4]);
    static bool Intersects(Geom::Quad2 quad, Geom::Line2 line);
    static bool IntersectX(Geom::Quad3 quad, Geom::Quad3 qSta, glm::vec3 velocity);
    static bool IntersectX(Geom::Quad3 quad, Geom::Line3 line);
    static bool IntersectY(Geom::Quad3 quad, Geom::Quad3 qSta, glm::vec3 velocity);
    static bool IntersectY(Geom::Quad3 quad, Geom::Line3 line);
    static bool IntersectZ(Geom::Quad3 quad, Geom::Quad3 qSta, glm::vec3 velocity);
    static bool IntersectZ(Geom::Quad3 quad, Geom::Line3 line);

private:
    glm::vec3 m_position;
    glm::vec3 m_min;
    glm::vec3 m_max;
};

#endif
