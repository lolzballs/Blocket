#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "util.h"

class RenderBlock
{
public:
    RenderBlock(int blockID, glm::vec3 position, bool* facesNeeded);
	virtual ~RenderBlock();

    int GetSize();
    inline glm::vec3* GetFaces() { return m_faces; }
private:
	int m_textureID;
    int m_size;
    glm::vec3* m_faces;

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
