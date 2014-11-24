#include "chunk.h"

Chunk::Chunk(int x, int y)
    : m_position(x, y), m_size(0)
{
    InitGL();
	AddBlock(1, glm::vec3(0, 0, 0));
    RebufferChunk();
}

Chunk::~Chunk()
{
}

void Chunk::InitGL()
{
    glGenBuffers(1, &m_vbo);
}

void Chunk::Render()
{
    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), 0);
//    glVertexAttribPointer(1, 2, GL_FLOAT, false, VERTEX_SIZE * sizeof(float), (GLvoid*) 12);
//    glVertexAttribPointer(2, 3, GL_FLOAT, false, VERTEX_SIZE * sizeof(float), (GLvoid*) 20);

    glDrawArrays(GL_QUADS, 0, m_size);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
//    glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
//    glDisableVertexAttribArray(2);
}

void Chunk::Update(float delta)
{

}

void Chunk::AddBlock(int blockID, glm::vec3 position)
{
    m_blocks.push_back(Block(blockID, position));
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

        m_size = renderBlock.GetSize();
        // TODO: Finish rebuffering
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_size, renderBlock.GetFaces(), GL_DYNAMIC_DRAW);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    }
}


// TODO: Actually get the required faces
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
