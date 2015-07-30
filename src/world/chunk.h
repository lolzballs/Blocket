#ifndef CHUNK_H
#define CHUNK_H

#include "../block/block.h"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 256

class Chunk
{
public:
    Chunk(int x, int y);

    virtual ~Chunk();

    void Render();

    void Update();

    void AddBlock(int blockID, glm::vec3 position, bool rebuffer);

    Block GetBlockAtPosition(glm::vec3 position);

    inline const glm::vec2 GetPosition()
    {
        return m_position;
    }

private:
    glm::vec2 m_position;
    Block m_blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
    GLuint m_vbo;
    GLsizei m_size;

    bool* GetFacesRequired(glm::vec3 position);
    void RebufferChunk();
    void InitGL();
};

#endif
