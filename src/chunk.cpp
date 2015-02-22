#include "chunk.h"

Chunk::Chunk(int x, int y)
        : m_position(x, y), m_size(0) {
    m_blocks = new Block **[CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE; i++) {
        m_blocks[i] = new Block *[CHUNK_HEIGHT];
        for (int j = 0; j < CHUNK_HEIGHT; j++) {
            m_blocks[i][j] = new Block[CHUNK_SIZE];
            for (int k = 0; k < CHUNK_SIZE; k++) {
                if (j == 0) {
                    m_blocks[i][j][k] = Block(1, glm::vec3(i, j, k));
                }
                else {
                    m_blocks[i][j][k] = Block(0, glm::vec3(i, j, k));
                }
            }
        }
    }

    InitGL();
    RebufferChunk();
}

Chunk::~Chunk() {
}

void Chunk::InitGL() {
    glGenBuffers(1, &m_vbo);
}

void Chunk::Render() {
    //glDisable(GL_CULL_FACE);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (GLvoid *) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (GLvoid *) 12);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (GLvoid *) 20);

    glDrawArrays(GL_QUADS, 0, (GLsizei) m_size);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
//    glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Chunk::Update() {

}

void Chunk::AddBlock(int blockID, glm::vec3 position, bool rebuffer) {
    m_blocks[(int) position.x][(int) position.y][(int) position.z] = Block(blockID, position);
    if (rebuffer) {
        RebufferChunk();
    }
}

Block Chunk::GetBlockAtPosition(glm::vec3 position) {
    return m_blocks[(int) position.x][(int) position.y][(int) position.z];
}

void Chunk::RebufferChunk() {
    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < CHUNK_SIZE; i++) {
        for (unsigned int j = 0; j < CHUNK_HEIGHT; j++) {
            for (unsigned int k = 0; k < CHUNK_SIZE; k++) {
                Block block = m_blocks[i][j][k];

                if (block.GetBlockID()) {
                    RenderBlock renderBlock = RenderBlock(block.GetBlockID(), block.GetPosition(), GetFacesRequired(block.GetPosition()));

                    Vertex *blockFaces = renderBlock.GetVertices();
                    for (unsigned int l = 0; l < renderBlock.GetSize(); l++) {
                        vertices.push_back(blockFaces[l]);
                    }
                }
            }
        }
    }

    m_size = vertices.size();

    float *floatVertices = Vertex::GetFloatArray(&vertices[0], m_size);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_size * VERTEX_SIZE * sizeof(float), floatVertices, GL_DYNAMIC_DRAW);
}


// TODO: Actually get the required faces
bool *Chunk::GetFacesRequired(glm::vec3 position) {
    bool *faces = new bool[6];
    faces[0] = true;
    faces[1] = true;
    faces[2] = true;
    faces[3] = true;
    faces[4] = true;
    faces[5] = true;
    return faces;
}
