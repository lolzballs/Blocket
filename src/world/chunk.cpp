#include "chunk.h"
#include "../util/vertex.h"

#include <vector>
#include <array>

Chunk::Chunk(Spritesheet& blocksheet, int x, int y, int z)
    : m_blocksheet(blocksheet),
    m_position(x, y, z),
    m_size(0)
{
    m_blocks = new int**[CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        m_blocks[i] = new int*[CHUNK_SIZE];
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            m_blocks[i][j] = new int[CHUNK_SIZE];
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                if (j == 0)
                {
                    m_blocks[i][j][k] = 1;
                }
                else
                {
                    m_blocks[i][j][k] = 0;
                }
            }
        }
    }

    InitGL();
    RebufferChunk();
}

Chunk::~Chunk()
{
    glDeleteBuffers(1, &m_vbo);

    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            delete[] m_blocks[i][j];
        }
        delete[] m_blocks[i];
    }
    delete[] m_blocks;
}

void Chunk::InitGL()
{
    glGenBuffers(1, &m_vbo);
}

void Chunk::Render(BasicShader& shader)
{
    shader.Enable();

    m_blocksheet.BindTexture();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (GLvoid*) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (GLvoid*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (GLvoid*) (5 * sizeof(float)));

    glDrawArrays(GL_QUADS, 0, (GLsizei) m_size);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Chunk::Update()
{
    if (m_changed)
    {
        RebufferChunk();
        m_changed = false;
    }
}

void Chunk::AddBlock(int x, int y, int z, int blockID)
{
    if (x < 0 || x > CHUNK_SIZE - 1 || y < 0 ||
        y > CHUNK_SIZE - 1 || z < 0 ||
        z > CHUNK_SIZE - 1)
    {
        return;
    }
    m_blocks[x][y][z] = blockID;
    m_changed = true;
}

int Chunk::GetBlockAtPosition(glm::ivec3 position)
{
    if (position.x < 0 || position.x > CHUNK_SIZE - 1 || position.y < 0 ||
        position.y > CHUNK_SIZE - 1 || position.z < 0 ||
        position.z > CHUNK_SIZE - 1)
    {
        return 0;
    }
    else
    {
        return m_blocks[position.x][position.y][position.z];
    }
}

void Chunk::RebufferChunk()
{
    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < CHUNK_SIZE; i++)
    {
        for (unsigned int j = 0; j < CHUNK_SIZE; j++)
        {
            for (unsigned int k = 0; k < CHUNK_SIZE; k++)
            {
                glm::vec3 position = glm::vec3(i, j, k) + m_position;
                int blockID = m_blocks[i][j][k];

                if (blockID != 0)
                {
                    auto tc = m_blocksheet.GetTexCoords(blockID);
                    bool* facesNeeded = GetFacesRequired(position);
                    if (facesNeeded[0])  // Top
                    {
                        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, -0.5) + position, tc[0]));
                        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, -0.5) + position, {tc[0].x, tc[1].y}));
                        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, 0.5) + position, tc[1]));
                        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, 0.5) + position, {tc[1].x, tc[0].y}));
                    }
                    if (facesNeeded[1])  // Down
                    {
                        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.5) + position, tc[0]));
                        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.5) + position, {tc[0].x, tc[1].y}));
                        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, -0.5) + position, tc[1]));
                        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, -0.5) + position, {tc[1].x, tc[0].y}));
                    }
                    if (facesNeeded[2])  // Left
                    {
                        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, 0.5) + position, {tc[1].x, tc[0].y}));
                        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, -0.5) + position, tc[0]));
                        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, -0.5) + position, {tc[0].x, tc[1].y}));
                        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.5) + position, tc[1]));
                    }
                    if (facesNeeded[3])  // Right
                    {
                        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.5) + position, {tc[0].x, tc[1].y}));
                        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, -0.5) + position, tc[1]));
                        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, -0.5) + position, {tc[1].x, tc[0].y}));
                        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, 0.5) + position, tc[0]));
                    }
                    if (facesNeeded[4])  // Front
                    {
                        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, 0.5) + position, {tc[1].x, tc[0].y}));
                        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, 0.5) + position, tc[0]));
                        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.5) + position, {tc[0].x, tc[1].y}));
                        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.5) + position, tc[1]));
                    }
                    if (facesNeeded[5])  // Back
                    {
                        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, -0.5) + position, {tc[0].x, tc[1].y}));
                        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, -0.5) + position, tc[1]));
                        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, -0.5) + position, {tc[1].x, tc[0].y}));
                        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, -0.5) + position, tc[0]));
                    }
                    delete[] facesNeeded;
                }
            }
        }
    }

    m_size = (GLsizei) vertices.size();

    float* floatVertices = Vertex::GetFloatArray(&vertices[0], m_size);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_size * VERTEX_SIZE * sizeof(float),
        floatVertices, GL_DYNAMIC_DRAW);

    delete[] floatVertices;
}

bool* Chunk::GetFacesRequired(glm::vec3 position)
{
    bool* faces = new bool[6]();

    if (!GetBlockAtPosition(position + glm::vec3(0, 1, 0)))
    {
        faces[0] = true;
    }
    if (!GetBlockAtPosition(position + glm::vec3(0, -1, 0)))
    {
        faces[1] = true;
    }
    if (!GetBlockAtPosition(position + glm::vec3(-1, 0, 0)))
    {
        faces[2] = true;
    }
    if (!GetBlockAtPosition(position + glm::vec3(1, 0, 0)))
    {
        faces[3] = true;
    }
    if (!GetBlockAtPosition(position + glm::vec3(0, 0, 1)))
    {
        faces[4] = true;
    }
    if (!GetBlockAtPosition(position + glm::vec3(0, 0, -1)))
    {
        faces[5] = true;
    }
    return faces;
}
