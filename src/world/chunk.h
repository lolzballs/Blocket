#ifndef CHUNK_H
#define CHUNK_H

#include "basicshader.h"
#include "util/spritesheet.h"

#define CHUNK_SIZE 16

class Chunk
{
public:
    Chunk(Spritesheet& blocksheet, int x, int y, int z);
    ~Chunk();

    void Render(BasicShader& shader);
    void Update();
    void AddBlock(int x, int y, int z, int blockID);
    int GetBlockAtPosition(glm::ivec3 position);

    inline glm::vec3 GetPosition() const
    {
        return m_position;
    }

private:
    Spritesheet& m_blocksheet;
    glm::vec3 m_position;
	int*** m_blocks;
    GLuint m_vbo;
    GLsizei m_size;
    bool m_changed;

    void InitGL();
    void RebufferChunk();
    bool* GetFacesRequired(glm::vec3 position);
};

#endif
