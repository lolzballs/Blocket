#ifndef CSIDE_H
#define CSIDE_H

#include "aabb.h"

#include <algorithm>

enum class CSide
{
    XN,
    YN,
    ZN,
    XP,
    YP,
    ZP
};

class CollisionSide
{
public:
    CollisionSide(Geom::Quad3 qStat, AABB aabb, glm::vec3 center, CSide type);
    ~CollisionSide();

    inline glm::vec3 GetCenter()
    {
        return m_center;
    }

    inline glm::vec3 GetQCenter()
    {
        return m_qCenter;
    }

    inline Geom::Quad3 GetQStat()
    {
        return m_qStat;
    }

    inline CSide GetType()
    {
        return m_type;
    }

    inline AABB GetAABB()
    {
        return m_aabb;
    }

private:
    Geom::Quad3 m_qStat;
    CSide m_type;
    AABB m_aabb;
    glm::vec3 m_center;
    glm::vec3 m_qCenter;
};

class CSideCompare
{
public:
    bool operator()(CollisionSide& s1, CollisionSide& s2)
    {
        glm::vec3 d1 = s1.GetCenter() - s1.GetQCenter();
        glm::vec3 d2 = s1.GetCenter() - s2.GetQCenter();
        float dist1 = glm::dot(d1, d1);
        float dist2 = glm::dot(d2, d2);
        // std::cout << dist1 << ", " << dist2 << std::endl;
        return dist1 < dist2;
    }
};

#endif
