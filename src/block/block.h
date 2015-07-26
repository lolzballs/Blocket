#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../util/vertex.h"
#include "../util/util.h"

class RenderBlock
{
public:
    RenderBlock(int blockID, glm::vec3 position, bool *facesNeeded);

    virtual ~RenderBlock();

    int GetSize();

    inline Vertex *GetVertices()
    {
        return &m_vertices[0];
    }

private:
    int m_textureID;
    int m_size;
    std::vector<Vertex> m_vertices;

    void SetUpFaces(glm::vec3 position, bool *facesNeeded);
};

class Block
{
public:
    Block();

    Block(int blockID, glm::vec3 position);

    virtual ~Block();

    inline int GetBlockID()
    {
        return m_blockID;
    }

    inline const glm::vec3 GetPosition()
    {
        return m_position;
    }

private:
    int m_blockID;
    glm::vec3 m_position;
};

#endif
