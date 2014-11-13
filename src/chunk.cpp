#include "chunk.h"

Chunk::Chunk(int x, int y)
	: m_position(x, y)
{
	AddBlock(1, glm::vec3(0, 0, 0));
}

Chunk::~Chunk()
{
}

void Chunk::Render()
{

}

void Chunk::Update(float delta)
{

}

void Chunk::AddBlock(int blockID, glm::vec3 position)
{
	m_blocks.push_back(Block(blockID, position += glm::vec3(m_position.x * 16, 0, m_position.y * 16)));
}

Block Chunk::GetBlockAtPosition(glm::vec3 position)
{
	for (unsigned long i = 0; i < m_blocks.size(); i++) 
	{
		if (m_blocks[i].GetPosition() == position)
		{
			return m_blocks[i];
		}
	}

	return Block(0, position);
}

void Chunk::RebufferChunk()
{
	for (unsigned long i = 0; i < m_blocks.size(); i++)
	{
		Block block = m_blocks[i];

		RenderBlock renderBlock = RenderBlock(block.GetBlockID(), block.GetPosition(), GetFacesRequired(block.GetPosition()));
        // TODO: Finish rebuffering
    }
}

bool* Chunk::GetFacesRequired(glm::vec3 position)
{
	bool* faces = new bool[6];
    faces[0] = true;
    faces[1] = true;
    faces[2] = true;
    faces[3] = true;
    faces[4] = true;
    faces[5] = true;
    return faces;
}
