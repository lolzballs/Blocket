#include "geom.h"
#include "aabb.h"

namespace Geom
{
glm::vec2 Point3FlattenX(glm::vec3 point)
{
    return glm::vec2(point.y, point.z);
}

glm::vec2 Point3FlattenY(glm::vec3 point)
{
    return glm::vec2(point.x, point.z);
}

glm::vec2 Point3FlattenZ(glm::vec3 point)
{
    return glm::vec2(point.x, point.y);
}

bool Line2::Intersects(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4)
{
    double denom =
        (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
    if (denom == 0.0)
    {
        return false;
    }
    double ua =
        ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denom;
    double ub =
        ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denom;

    return ua >= 0.0 && ua < 1.0 && ub >= 0.0 && ub <= 1.0;
}

bool Line2::Intersects(Line2 a, Line2 b)
{
    return Intersects(a.start, a.end, b.start, b.end);
}

Line2 Line3::FlattenX()
{
    return {Point3FlattenX(start), Point3FlattenX(end)};
}

Line2 Line3::FlattenY()
{
    return {Point3FlattenY(start), Point3FlattenY(end)};
}

Line2 Line3::FlattenZ()
{
    return {Point3FlattenZ(start), Point3FlattenZ(end)};
}

AABB Line3::ToAABB()
{
	return AABB({ std::min(start.x, end.x), std::min(start.y, end.y), std::min(start.z, end.z) }, { 0, 0, 0 }, { std::abs(start.x - end.x), std::abs(start.y - end.y), std::abs(start.z - end.z) });
}
}
