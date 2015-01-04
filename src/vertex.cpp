#include <iostream>
#include "vertex.h"

float* Vertex::GetFloatArray(Vertex *vertices, unsigned int size)
{
	float* array = new float[size * VERTEX_SIZE];
	for (unsigned int i = 0; i < size; i++)
	{
		array[i * VERTEX_SIZE + 0] = vertices[i].m_position.x;
		array[i * VERTEX_SIZE + 1] = vertices[i].m_position.y;
		array[i * VERTEX_SIZE + 2] = vertices[i].m_position.z;
		array[i * VERTEX_SIZE + 3] = vertices[i].m_texCoord.x;
		array[i * VERTEX_SIZE + 4] = vertices[i].m_texCoord.y;
		array[i * VERTEX_SIZE + 5] = vertices[i].m_color.r;
		array[i * VERTEX_SIZE + 6] = vertices[i].m_color.g;
		array[i * VERTEX_SIZE + 7] = vertices[i].m_color.b;
		array[i * VERTEX_SIZE + 8] = vertices[i].m_color.a;
	}
	return array;
}

Vertex::Vertex(glm::vec3 position)
	: m_position(position), m_color(glm::vec4(0, 0, 0, 1)), m_texCoord(glm::vec3())
{
}

Vertex::Vertex(glm::vec3 position, glm::vec4 color)
	: m_position(position), m_color(color), m_texCoord(glm::vec3())
{
}

Vertex::Vertex(glm::vec3 position, glm::vec2 texCoord)
	: m_position(position), m_color(glm::vec4(0, 0, 0, 1)), m_texCoord(texCoord)
{
}

Vertex::Vertex(glm::vec3 position, glm::vec2 texCoord, glm::vec4 color)
	: m_position(position), m_texCoord(texCoord), m_color(color)
{
}

Vertex::~Vertex()
{
}

