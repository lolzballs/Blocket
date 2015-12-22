#include "player.h"
#include "util/util.h"

#include <glm/ext.hpp>
#include <glad/glad.h>

Player::Player(World& world, glm::vec3 position, glm::vec2 rotation, float speed)
    : Entity(world,
             AABB(position, glm::vec3(-0.4, 0, -0.4), glm::vec3(0.4, 1.8, 0.4)),
             rotation, speed),
	  m_blockSelected(glm::vec3(), glm::vec3(), glm::vec3())
{
    InitGL();
}

Player::~Player()
{
    glDeleteBuffers(1, &m_vbo);
}

void Player::InitGL()
{
    glGenBuffers(1, &m_vbo);
}

void Player::BufferBoundingBox(float delta)
{
//  glm::vec3 position = Util::Vector::Lerp(m_oldposition, m_position, delta);
//  AABB lerped = AABB(position, glm::vec3(-0.4, 0, -0.4), glm::vec3(0.4, 1.8, 0.4));

//  std::array<Vertex, 32> playerVertices = lerped.GetBoundingBoxVertices();
//	float* playerData = Vertex::GetFloatArray(playerVertices.data(), playerVertices.size());

	glm::vec3 expand(0.005);
	std::array<Vertex, 32> selectVertices = m_blockSelected.Expand(expand).Expand(-expand).GetBoundingBoxVertices(glm::vec4(0, 0, 0, 1));
	float* selectData = Vertex::GetFloatArray(selectVertices.data(), selectVertices.size());
	
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, selectVertices.size() * VERTEX_SIZE * sizeof(float), selectData, GL_DYNAMIC_DRAW);

//	delete[] playerData;
	delete[] selectData;
//	delete[] combinedData;
}

void Player::Update(InputHandler& input)
{
    m_oldposition = m_position;
    m_oldrotation = m_rotation;

    glm::vec2 mouseDelta = input.GetMouseDelta();
    m_rotation += glm::vec2(mouseDelta.y, mouseDelta.x) * 0.25;

    if (m_rotation.x > 90)
    {
        m_rotation.x = 90;
    }
    else if (m_rotation.x < -90)
    {
        m_rotation.x = -90;
    }

	m_blockSelected = m_world.Raytrace(m_position + glm::vec3(0, 1.5, 0), m_rotation, 5);

    glm::vec3 movement;
    if (input.IsKeyDown(GLFW_KEY_W))
    {
        movement += glm::vec3(cos(glm::radians(m_rotation.y - 90)), 0,
                              sin(glm::radians(m_rotation.y - 90)));
    }
    if (input.IsKeyDown(GLFW_KEY_S))
    {
        movement += glm::vec3(cos(glm::radians(m_rotation.y + 90)), 0,
                              sin(glm::radians(m_rotation.y + 90)));
    }
    if (input.IsKeyDown(GLFW_KEY_A))
    {
        movement += glm::vec3(cos(glm::radians(m_rotation.y + 180)), 0,
                              sin(glm::radians(m_rotation.y + 180)));
    }
    if (input.IsKeyDown(GLFW_KEY_D))
    {
        movement += glm::vec3(cos(glm::radians(m_rotation.y)), 0,
                              sin(glm::radians(m_rotation.y)));
    }
    if (input.IsKeyDown(GLFW_KEY_SPACE) && m_onground)
    {
        movement += glm::vec3(0, 1, 0);
    }
    if (input.IsKeyDown(GLFW_KEY_LEFT_SHIFT))
    {
        movement += glm::vec3(0, -1, 0);
    }

    // Clamp movement magnitude to 1
    float length = glm::length(movement);
    if (length > 1)
    {
        movement = glm::normalize(movement);
    }
    else if (length < -1)
    {
        movement = -glm::normalize(movement);
    }

    Move(movement);
}

void Player::Render(float delta)
{
	BufferBoundingBox(delta);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (GLvoid*)(5 * sizeof(float)));

    glDrawArrays(GL_LINES, 0, (GLsizei)24);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

glm::vec3 Player::GetPlayerRenderPosition(float delta)
{
    return GetRenderPosition(delta) + glm::vec3(0, 1.5, 0);
}
