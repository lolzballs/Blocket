#ifndef BLOCK_H
#define BLOCK_H

#include "../util/vertex.h"
#include "../util/aabb.h"

#include <vector>

class RenderBlock
{
public:
    RenderBlock(int blockID, glm::vec3 position, bool* facesNeeded);
    ~RenderBlock();

    inline unsigned int GetSize()
    {
        return m_size;
    }

    inline Vertex* GetVertices()
    {
        return &m_vertices[0];
    }

private:
    int m_textureID;
    int m_size;
    std::vector<Vertex> m_vertices;

    void SetUpFaces(glm::vec3 position, bool* facesNeeded);
};

#endif
