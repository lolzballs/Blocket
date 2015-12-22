#ifndef WORLD_H
#define WORLD_H

#include "../input.h"
#include "chunk.h"
#include "basicshader.h"
#include "../util/cside.h"

class World
{
public:
    World();  // TODO: World flags
    ~World();

    void Update(InputHandler& input);
    void Render(BasicShader& shader);
    std::vector<AABB> GetIntersectingAABBs(AABB aabb);
	AABB Raytrace(glm::vec3 position, glm::vec2 rotation, float reach);

private:
    Chunk m_chunk;  // TODO: Find way of handling chunks
	GLuint m_vbo;
};

#endif
