#include "block.h"

RenderBlock::RenderBlock(int blockID, glm::vec3 position, bool facesNeeded[])
    : m_size(0)
{
	SetUpFaces(position, facesNeeded);
	std::stringstream texturepath;
	texturepath << "./res/textures/blocks/" << blockID << ".png";

	m_textureID = loadTexture(texturepath.str());	
	std::cout << m_textureID << std::endl;
}

RenderBlock::~RenderBlock()
{
    delete[] m_faces;
}

void RenderBlock::SetUpFaces(glm::vec3 position, bool facesNeeded[])
{
    m_faces = new glm::vec3[24]; // TODO: GET ACTUAL SIZE
	if (facesNeeded[0]) // Top
	{
        m_faces[0] = glm::vec3(0.5, 0.5, 0.5);
        m_faces[1] = glm::vec3(-0.5, 0.5, 0.5);
        m_faces[2] = glm::vec3(-0.5, 0.5, -0.5);
        m_faces[3] = glm::vec3(0.5, 0.5, -0.5);
        m_size += 4;
	}
	if (facesNeeded[1]) // Down
	{
        m_faces[0] = glm::vec3(0.5, -0.5, -0.5);
        m_faces[1] = glm::vec3(-0.5, -0.5, -0.5);
        m_faces[2] = glm::vec3(-0.5, -0.5, 0.5);
        m_faces[3] = glm::vec3(0.5, -0.5, 0.5);
        m_size += 4;
	}
	if (facesNeeded[2]) // Left
	{
        m_faces[0] = glm::vec3(-0.5, 0.5, 0.5);
        m_faces[1] = glm::vec3(-0.5, 0.5, -0.5);
        m_faces[2] = glm::vec3(-0.5, -0.5, -0.5);
        m_faces[3] = glm::vec3(-0.5, -0.5, 0.5);
        m_size += 4;
	}
	if (facesNeeded[3]) // Right
	{
        m_faces[0] = glm::vec3(0.5, -0.5, 0.5);
        m_faces[1] = glm::vec3(0.5, -0.5, -0.5);
        m_faces[2] = glm::vec3(0.5, 0.5, -0.5);
        m_faces[3] = glm::vec3(0.5, 0.5, 0.5);
        m_size += 4;
	}
	if (facesNeeded[4]) // Front
	{
        m_faces[0] = glm::vec3(0.5, 0.5, 0.5);
        m_faces[1] = glm::vec3(-0.5, 0.5, 0.5);
        m_faces[2] = glm::vec3(-0.5, -0.5, 0.5);
        m_faces[3] = glm::vec3(0.5, -0.5, 0.5);
        m_size += 4;
	}
	if (facesNeeded[5]) // Back
	{
        m_faces[0] = glm::vec3(0.5, -0.5, -0.5);
        m_faces[1] = glm::vec3(-0.5, -0.5, -0.5);
        m_faces[2] = glm::vec3(-0.5, 0.5, -0.5);
        m_faces[3] = glm::vec3(0.5, 0.5, -0.5);
        m_size += 4;
	}
}

int RenderBlock::GetSize()
{
    return m_size;
}

Block::Block()
	:m_blockID(0)
{

}

Block::Block(int blockID, glm::vec3 position)
	: m_blockID(blockID), m_position(position)
{

}

Block::~Block()
{

}


