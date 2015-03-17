#include <glm/glm.hpp>

typedef struct {
	glm::vec2 start;
	glm::vec2 end;
} Line2;

typedef struct {
	glm::vec3 start;
	glm::vec3 end;
} Line3;

typedef struct {
	glm::vec2 a;
	glm::vec2 b;
	glm::vec2 c;
	glm::vec2 d;	
} Quad2;

typedef struct {
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	glm::vec3 d;	
} Quad3;

glm::vec3 Quad3CenterPoint(Quad3 quad) {
	return (quad.a + quad.b + quad.c + quad.d) / 4.0f;
}

glm::vec2 Point3FlattenX(glm::vec3 point) {
	return glm::vec2(point.y, point.z);
}

glm::vec2 Point3FlattenY(glm::vec3 point) {
	return glm::vec2(point.x, point.z);
}

glm::vec2 Point3FlattenZ(glm::vec3 point) {
	return glm::vec2(point.x, point.y);
}

Line2 Line3FlattenX(Line3 line) {
	return {Point3FlattenX(line.start), Point3FlattenZ(line.end)};	
}

Line2 Line3FlattenY(Line3 line) {
	return {Point3FlattenY(line.start), Point3FlattenY(line.end)};	
}

Line2 Line3FlattenZ(Line3 line) {
	return {Point3FlattenZ(line.start), Point3FlattenZ(line.end)};
}

bool LineIntersect(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4) {
	double denom = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
	if (denom == 0.0) {
		return false;
	}
	double ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denom;
	double ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denom;

    return ua >= 0.0 && ua < 1.0 && ub >= 0.0 && ub <= 1.0;	
}

bool LineIntersect(Line2 a, Line2 b) {
	return LineIntersect(a.start, a.end, b.start, b.end);
}

