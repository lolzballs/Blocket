#ifndef GEOM_H
#define GEOM_H

#include <glm/glm.hpp>

namespace Geom
{
glm::vec2 Point3FlattenX(glm::vec3 point);

glm::vec2 Point3FlattenY(glm::vec3 point);

glm::vec2 Point3FlattenZ(glm::vec3 point);

struct Line2
{
    glm::vec2 start;
    glm::vec2 end;

    static bool Intersects(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4);
    static bool Intersects(Line2 a, Line2 b);
};

struct Line3
{
    glm::vec3 start;
    glm::vec3 end;

    Line2 FlattenX();
    Line2 FlattenY();
    Line2 FlattenZ();
};

struct Quad2
{
    glm::vec2 a;
    glm::vec2 b;
    glm::vec2 c;
    glm::vec2 d;
};

struct Quad3
{
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;
    glm::vec3 d;

    inline glm::vec3 GetCenter()
    {
        return (a + b + c + d) / 4.0f;
    };
};
}

#endif
