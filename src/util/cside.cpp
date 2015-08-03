#include "cside.h"

CollisionSide::CollisionSide(Geom::Quad3 qStat, AABB aabb, glm::vec3 center, char type)
    : m_qStat(qStat),
    m_type(type),
    m_aabb(aabb),
    m_center(center),
    m_qCenter(qStat.GetCenter())
{
}

CollisionSide::~CollisionSide()
{
}
