#ifndef WORLD_H
#define WORLD_H

#include "../input.h"
#include "chunk.h"

class World
{
public:
    World();  // TODO: World flags
    ~World();

    void Update(InputHandler input);
    void Render();

private:
    Chunk m_chunk;  // TODO: Find way of handling chunks
};

#endif
