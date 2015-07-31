#ifndef WORLD_H
#define WORLD_H

#include "../input.h"
#include "chunk.h"
#include <iostream>

class World
{
public:
    World();  // TODO: World flags
    ~World();

    void Update(InputHandler input);
    void Render();
    std::vector<AABB> GetBlockAABB(glm::vec3 location);
    std::vector<AABB> GetIntersectingAABBs(AABB aabb);

private:
    Chunk m_chunk;  // TODO: Find way of handling chunks
};

#endif
