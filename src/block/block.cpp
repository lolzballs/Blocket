#include "block.h"

RenderBlock::RenderBlock(int blockID, glm::vec3 position, bool* facesNeeded)
        : m_size(0) {
    SetUpFaces(position, facesNeeded);
    std::stringstream texturepath;
    texturepath << "./res/textures/blocks/" << blockID << ".png";

    m_textureID = loadTexture(texturepath.str());
}

RenderBlock::~RenderBlock() {
}

void RenderBlock::SetUpFaces(glm::vec3 position, bool* facesNeeded) {
    std::vector<Vertex> vertices;
    if (facesNeeded[0]) // Top
    {
        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, -0.5) + position, glm::vec4(1, 0, 1, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, -0.5) + position, glm::vec4(1, 0, 1, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, 0.5) + position, glm::vec4(1, 0, 1, 1)));
        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, 0.5) + position, glm::vec4(1, 0, 1, 1)));
        m_size += 4;
    }
    if (facesNeeded[1]) // Down
    {
        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.5) + position, glm::vec4(0, 1, 0, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.5) + position, glm::vec4(0, 1, 0, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, -0.5) + position, glm::vec4(0, 1, 0, 1)));
        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, -0.5) + position, glm::vec4(0, 1, 0, 1)));
        m_size += 4;
    }
    if (facesNeeded[2]) // Left
    {
        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, 0.5) + position, glm::vec4(1, 1, 0, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, -0.5) + position, glm::vec4(1, 1, 0, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, -0.5) + position, glm::vec4(1, 1, 0, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.5) + position, glm::vec4(1, 1, 0, 1)));
        m_size += 4;
    }
    if (facesNeeded[3]) // Right
    {
        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.5) + position, glm::vec4(0, 0, 1, 1)));
        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, -0.5) + position, glm::vec4(0, 0, 1, 1)));
        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, -0.5) + position, glm::vec4(0, 0, 1, 1)));
        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, 0.5) + position, glm::vec4(0, 0, 1, 1)));
        m_size += 4;
    }
    if (facesNeeded[4]) // Front
    {
        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, 0.5) + position, glm::vec4(0, 1, 1, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, 0.5) + position, glm::vec4(0, 1, 1, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.5) + position, glm::vec4(0, 1, 1, 1)));
        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.5) + position, glm::vec4(0, 1, 1, 1)));
        m_size += 4;
    }
    if (facesNeeded[5]) // Back
    {
        vertices.push_back(Vertex(glm::vec3(0.5, -0.5, -0.5) + position, glm::vec4(1, 0, 0, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, -0.5) + position, glm::vec4(1, 0, 0, 1)));
        vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, -0.5) + position, glm::vec4(1, 0, 0, 1)));
        vertices.push_back(Vertex(glm::vec3(0.5, 0.5, -0.5) + position, glm::vec4(1, 0, 0, 1)));
        m_size += 4;
    }
    m_vertices = vertices;
}

int RenderBlock::GetSize() {
    return m_size;
}

Block::Block()
        : m_blockID(0) {

}

Block::Block(int blockID, glm::vec3 position)
        : m_blockID(blockID), m_position(position) {

}

Block::~Block() {

}
