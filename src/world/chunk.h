#ifndef CHUNK_H
#define CHUNK_H

#include "basicshader.h"

#include <array>

#define CHUNK_SIZE 16

class Chunk
{
public:
    Chunk(int x, int y);
    ~Chunk();

    void Render(BasicShader& shader);
    void Update();
    void AddBlock(int blockID, glm::vec3 position);
    int GetBlockAtPosition(glm::vec3 position);

    inline const glm::vec2 GetPosition()
    {
        return m_position;
    }

private:
    glm::vec2 m_position;
    std::array<int, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE> m_blocks;
    GLuint m_vbo;
    GLsizei m_size;
    bool m_changed;

    void InitGL();
    void RebufferChunk();
    bool* GetFacesRequired(glm::vec3 position);

    int GetArrayPosition(int x, int y, int z);
    int GetArrayPosition(glm::vec3 position);
};

#endif
