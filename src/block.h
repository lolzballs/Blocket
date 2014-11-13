#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "util.h"

class RenderBlock
{
public:
    RenderBlock(int blockID, glm::vec3 position, bool* facesNeeded);
	virtual ~RenderBlock();

	inline glm::vec3* GetUpFace() { return m_upFace; }
	inline glm::vec3* GetDownFace() { return m_downFace; }
	inline glm::vec3* GetLeftFace() { return m_leftFace; }
	inline glm::vec3* GetRightFace() { return m_rightFace; }
	inline glm::vec3* GetFrontFace() { return m_frontFace; }
	inline glm::vec3* GetBackFace() { return m_backFace; }
private:
	int m_textureID;
	glm::vec3* m_upFace;
	glm::vec3* m_downFace;
	glm::vec3* m_leftFace;
	glm::vec3* m_rightFace;
	glm::vec3* m_frontFace;
	glm::vec3* m_backFace;

	void SetUpFaces(glm::vec3 position, bool facesNeeded[]);
};

class Block
{
public:
	Block();
	Block(int blockID, glm::vec3 position);
	virtual ~Block();

	inline int GetBlockID() { return m_blockID; }
	inline const glm::vec3 GetPosition() { return m_position; }
private:
	int m_blockID;
	glm::vec3 m_position;
};

#endif
