#include "aabb.h"

AABB::AABB(glm::vec3 position, glm::vec3 min, glm::vec3 max)
		: m_position(position) {
	m_min = position + min;
	m_max = position + max;
}

AABB::~AABB() {

}

bool AABB::Intersects(AABB other) {
	double minX = std::max(m_min.x, other.m_min.x);
	double minY = std::max(m_min.y, other.m_min.y);
	double minZ = std::max(m_min.z, other.m_min.z);
	double maxX = std::min(m_max.x, other.m_max.x);
	double maxY = std::min(m_max.y, other.m_max.y);
	double maxZ = std::min(m_max.z, other.m_max.z);
	return !(minX > maxX || minY > maxY || minZ > maxZ);
}

bool AABB::Contains(glm::vec2 point, glm::vec2 points[4]) {
	int j = 3;
	bool oddNodes = false;
	for (unsigned int i = 0; i < 4; j = i++) {
		if ((((points[i].y <= point.y) && (point.y < points[j].y)) ||
				((points[j].y <= point.y) && (point.y < points[i].y))) &&
				(point.x < (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)) {
			oddNodes = !oddNodes;
		}
	}
	return oddNodes;
}

bool AABB::Intersects(Quad2 quad, Line2 line) {
	if (LineIntersect(quad.a, quad.b, line.start, line.end)) {
		return true;
	}	
	if (LineIntersect(quad.b, quad.c, line.start, line.end)) {
		return true;
	}
	if (LineIntersect(quad.c, quad.d, line.start, line.end)) {
		return true;
	}
	if (LineIntersect(quad.d, quad.a, line.start, line.end)) {
		return true;
	}
	glm::vec2 points[4] = {quad.a, quad.b, quad.c, quad.d};
	if (Contains(line.start, points)) {
		return true;
	}
	if (Contains(line.end, points)) {
		return true;
	}
	return false;
}

bool AABB::IntersectX(Quad3 quad, Quad3 qSta, glm::vec3 velocity) {
	Quad2 q1 = {Point3FlattenY(quad.a), Point3FlattenY(quad.b), Point3FlattenY(quad.b + velocity), Point3FlattenY(quad.a + velocity)};
	Quad2 q2 = {Point3FlattenZ(quad.b), Point3FlattenZ(quad.c), Point3FlattenZ(quad.c + velocity), Point3FlattenZ(quad.b + velocity)};
	Line2 l1 = {Point3FlattenY(qSta.a), Point3FlattenY(qSta.b)};
	Line2 l2 = {Point3FlattenZ(qSta.b), Point3FlattenZ(qSta.c)};
	return Intersects(q1, l1) && Intersects(q2, l2);
}

bool AABB::IntersectX(Quad3 quad, Line3 line) {
	Line2 q1 = {Point3FlattenY(quad.a), Point3FlattenY(quad.b)};
	Line2 q2 = {Point3FlattenZ(quad.b), Point3FlattenZ(quad.c)};
	Line2 l1 = Line3FlattenY(line);
	Line2 l2 = Line3FlattenZ(line);
	return LineIntersect(q1.start, q1.end, l1.start, l1.end) && LineIntersect(q2.start, q2.end, l2.start, l2.end);
}

bool AABB::IntersectY(Quad3 quad, Quad3 qSta, glm::vec3 velocity) {
	Quad2 q1 = {Point3FlattenX(quad.a), Point3FlattenX(quad.b), Point3FlattenX(quad.b + velocity), Point3FlattenX(quad.a + velocity)};
	Quad2 q2 = {Point3FlattenZ(quad.b), Point3FlattenZ(quad.c), Point3FlattenZ(quad.c + velocity), Point3FlattenZ(quad.b + velocity)};
	Line2 l1 = {Point3FlattenX(qSta.a), Point3FlattenX(qSta.b)};
	Line2 l2 = {Point3FlattenZ(qSta.b), Point3FlattenZ(qSta.c)};
	return Intersects(q1, l1) && Intersects(q2, l2);
}

bool AABB::IntersectY(Quad3 quad, Line3 line) {
	Line2 q1 = {Point3FlattenX(quad.a), Point3FlattenX(quad.b)};
	Line2 q2 = {Point3FlattenZ(quad.b), Point3FlattenZ(quad.c)};
	Line2 l1 = Line3FlattenX(line);
	Line2 l2 = Line3FlattenZ(line);
	return LineIntersect(q1.start, q1.end, l1.start, l1.end) && LineIntersect(q2.start, q2.end, l2.start, l2.end);

}

bool AABB::IntersectZ(Quad3 quad, Quad3 qSta, glm::vec3 velocity) {
	Quad2 q1 = {Point3FlattenX(quad.a), Point3FlattenX(quad.b), Point3FlattenX(quad.b + velocity), Point3FlattenX(quad.a + velocity)};
	Quad2 q2 = {Point3FlattenY(quad.b), Point3FlattenY(quad.c), Point3FlattenY(quad.c + velocity), Point3FlattenY(quad.b + velocity)};
	Line2 l1 = {Point3FlattenX(qSta.a), Point3FlattenX(qSta.b)};
	Line2 l2 = {Point3FlattenY(qSta.b), Point3FlattenY(qSta.c)};
	return Intersects(q1, l1) && Intersects(q2, l2);
}

bool AABB::IntersectZ(Quad3 quad, Line3 line) {
	Line2 q1 = {Point3FlattenX(quad.a), Point3FlattenX(quad.b)};
	Line2 q2 = {Point3FlattenY(quad.b), Point3FlattenY(quad.c)};
	Line2 l1 = Line3FlattenX(line);
	Line2 l2 = Line3FlattenY(line);
	return LineIntersect(q1.start, q1.end, l1.start, l1.end) && LineIntersect(q2.start, q2.end, l2.start, l2.end);

}

