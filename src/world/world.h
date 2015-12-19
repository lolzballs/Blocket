#ifndef WORLD_H
#define WORLD_H

#include "../input.h"
#include "chunk.h"
#include "basicshader.h"

class World
{
public:
    World();  // TODO: World flags
    ~World();

    void Update(InputHandler& input);
    void Render(BasicShader& shader);
    std::vector<AABB> GetBlockAABBs(glm::vec3 location);
    std::vector<AABB> GetIntersectingAABBs(AABB aabb);

private:
    Chunk m_chunk;  // TODO: Find way of handling chunks
};

#endif
