#include "block.h"

RenderBlock::RenderBlock(int blockID, glm::vec3 position, bool facesNeeded[])
{
	SetUpFaces(position, facesNeeded);
	std::stringstream texturepath;
	texturepath << "./res/textures/blocks/" << blockID << ".png";

	m_textureID = loadTexture(texturepath.str());	
	std::cout << m_textureID << std::endl;
}

RenderBlock::~RenderBlock()
{
	delete[] m_upFace;
	delete[] m_downFace;
	delete[] m_leftFace;
	delete[] m_rightFace;
	delete[] m_frontFace;
	delete[] m_backFace;	
}

void RenderBlock::SetUpFaces(glm::vec3 position, bool facesNeeded[])
{
	if (facesNeeded[0]) // Top
	{
		glm::vec3 topCenterPosition = position + glm::vec3(0, 0.5, 0);
		m_upFace = new glm::vec3[4];
		m_upFace[0] = topCenterPosition + glm::vec3(0.5, 0, 0.5);
		m_upFace[1] = topCenterPosition + glm::vec3(-0.5, 0, 0.5);
		m_upFace[2] = topCenterPosition + glm::vec3(-0.5, 0, -0.5);
		m_upFace[3] = topCenterPosition + glm::vec3(0.5, 0, -0.5);
	}
	if (facesNeeded[1]) // Down
	{
		glm::vec3 downCenterPosition = position + glm::vec3(0, -0.5, 0);
		m_downFace = new glm::vec3[4];
		m_downFace[0] = downCenterPosition + glm::vec3(0.5, 0, -0.5);
		m_downFace[1] = downCenterPosition + glm::vec3(-0.5, 0, -0.5);
		m_downFace[2] = downCenterPosition + glm::vec3(-0.5, 0, 0.5);
		m_downFace[3] = downCenterPosition + glm::vec3(0.5, 0, 0.5);
	}
	if (facesNeeded[2]) // Left
	{
		glm::vec3 leftCenterPosition = position + glm::vec3(-0.5, 0, 0);
		m_leftFace = new glm::vec3[4];
		m_leftFace[0] = leftCenterPosition + glm::vec3(0, 0.5, 0.5);
		m_leftFace[1] = leftCenterPosition + glm::vec3(0, 0.5, -0.5);
		m_leftFace[2] = leftCenterPosition + glm::vec3(0, -0.5, -0.5);
		m_leftFace[3] = leftCenterPosition + glm::vec3(0, -0.5, 0.5);
	}
	if (facesNeeded[3]) // Right
	{
		glm::vec3 rightCenterPosition = position + glm::vec3(0.5, 0, 0);
		m_rightFace = new glm::vec3[4];
		m_rightFace[0] = rightCenterPosition + glm::vec3(0, -0.5, 0.5);
		m_rightFace[1] = rightCenterPosition + glm::vec3(0, -0.5, -0.5);
		m_rightFace[2] = rightCenterPosition + glm::vec3(0, 0.5, -0.5);
		m_rightFace[3] = rightCenterPosition + glm::vec3(0, 0.5, 0.5);
	}
	if (facesNeeded[4]) // Front
	{
		glm::vec3 frontCenterPosition = position + glm::vec3(0, 0, 0.5);
		m_frontFace = new glm::vec3[4];
		m_frontFace[0] = frontCenterPosition + glm::vec3(0.5, 0.5, 0);
		m_frontFace[1] = frontCenterPosition + glm::vec3(-0.5, 0.5, 0);
		m_frontFace[2] = frontCenterPosition + glm::vec3(-0.5, -0.5, 0);
		m_frontFace[3] = frontCenterPosition + glm::vec3(0.5, -0.5, 0);
	}
	if (facesNeeded[5]) // Back
	{
		glm::vec3 backCenterPosition = position + glm::vec3(0, 0, -0.5);
		m_backFace = new glm::vec3[4];
		m_backFace[0] = backCenterPosition + glm::vec3(0.5, -0.5, 0);
		m_backFace[1] = backCenterPosition + glm::vec3(-0.5, -0.5, 0);
		m_backFace[2] = backCenterPosition + glm::vec3(-0.5, 0.5, 0);
		m_backFace[3] = backCenterPosition + glm::vec3(0.5, 0.5, 0);
	}
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


