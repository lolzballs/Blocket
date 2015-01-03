#include "chunk.h"

Chunk::Chunk(int x, int y)
    : m_position(x, y), m_size(0)
{
    InitGL();
	AddBlock(1, glm::vec3(0, 0, 0));
//    AddBlock(1, glm::vec3(0, 1, 1));
//    AddBlock(1, glm::vec3(1, 1, 0));
//    AddBlock(1, glm::vec3(1, 1, 1));
//    AddBlock(1, glm::vec3(0, 1, -1));
//    AddBlock(1, glm::vec3(-1, 1, 0));
//    AddBlock(1, glm::vec3(-1, 1, -1));
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
    //glDisable(GL_CULL_FACE);
    std::cout << m_size << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    glVertexAttribPointer(1, 2, GL_FLOAT, false, VERTEX_SIZE * sizeof(float), (GLvoid*) 12);
//    glVertexAttribPointer(2, 3, GL_FLOAT, false, VERTEX_SIZE * sizeof(float), (GLvoid*) 20);

    glDrawArrays(GL_QUADS, 0, (GLsizei) m_size);
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
    std::vector<glm::vec3> faces;
	for (unsigned long i = 0; i < m_blocks.size(); i++)
	{
		Block block = m_blocks[i];

        RenderBlock renderBlock = RenderBlock(block.GetBlockID(), block.GetPosition(), GetFacesRequired(block.GetPosition()));

        glm::vec3* blockFaces = renderBlock.GetFaces();
        for (unsigned int j = 0; j < renderBlock.GetSize(); j++)
        {
            faces.push_back(blockFaces[j]);
        }
        m_size += renderBlock.GetSize();
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_size * 3 * sizeof(float), &faces[0], GL_DYNAMIC_DRAW);
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
