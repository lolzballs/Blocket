#ifndef CHUNK_H
#define CHUNK_H

#include "../block/block.h"

#include <array>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 256

class Chunk
{
public:
    Chunk(int x, int y);
    ~Chunk();

    void Render();
    void Update();
    void AddBlock(int blockID, glm::vec3 position, bool rebuffer);
    int GetBlockAtPosition(glm::vec3 position);

    inline const glm::vec2 GetPosition()
    {
        return m_position;
    }

private:
    glm::vec2 m_position;
    std::array<int, CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE> m_blocks;
    GLuint m_vbo;
    GLsizei m_size;

    void InitGL();
    void RebufferChunk();
    bool* GetFacesRequired(glm::vec3 position);

    int GetArrayPosition(int x, int y, int z);
    int GetArrayPosition(glm::vec3 position);
};

#endif
