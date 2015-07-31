#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>
#include <algorithm>

#include "geom.h"
#include <iostream>

class AABB
{
public:
    AABB(glm::vec3 position, glm::vec3 min, glm::vec3 max);
    ~AABB();

    inline void SetPosition(glm::vec3 position)
    {
        m_position = position;
    }

    inline glm::vec3 GetPosition()
    {
        return m_position;
    }

    inline void SetMin(glm::vec3 min)
    {
        std::cout << "YOU ARE NOT SUPPOSED TO MODIFY THIS!!!! FREAKING CRAP" << std::endl;
        m_min = min;
    }

    inline glm::vec3 GetMin()
    {
        return m_min;
    }

    inline void SetMax(glm::vec3 max)
    {
        m_max = max;
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

    inline AABB Expand(glm::vec3 amount)
    {
        float minX = m_min[0] + (amount[0] > 0 ? 0 : amount[0]);
        float minY = m_min[1] + (amount[1] > 0 ? 0 : amount[1]);
        float minZ = m_min[2] + (amount[2] > 0 ? 0 : amount[2]);

        float maxX = m_max[0] + (amount[0] < 0 ? 0 : amount[0]);
        float maxY = m_max[1] + (amount[1] < 0 ? 0 : amount[1]);
        float maxZ = m_max[2] + (amount[2] < 0 ? 0 : amount[2]);

        return AABB(m_position, glm::vec3(minX, minY, minZ), glm::vec3(maxX, maxY, maxZ));
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
