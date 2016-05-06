#ifndef WORLD_H
#define WORLD_H

#define CHUNK_VIEW_DISTANCE 2

#include "../input.h"
#include "chunk.h"
#include "basicshader.h"
#include "../util/cside.h"

class World
{
public:
    World(Spritesheet& blocksheet);  // TODO: World flags
    ~World();

    void Update(InputHandler& input);
    void Render(BasicShader& shader);
    std::vector<AABB> GetIntersectingAABBs(AABB aabb);
    AABB Raytrace(glm::vec3 position, glm::vec2 rotation, float reach);

private:
    Chunk m_chunk;  // TODO: Find way of handling chunks
};

#endif
