#include "block.h"

#include "../util/util.h"

#include <iostream>
#include <sstream>
#include <string>

RenderBlock::RenderBlock(int blockID, glm::vec3 position, bool* facesNeeded)
    : m_size(0)
{
    SetUpFaces(position, facesNeeded);
    std::stringstream texturepath;
    texturepath << "./res/textures/blocks/" << blockID << ".png";

    m_textureID = Util::Texture::LoadTexture(texturepath.str());
}

RenderBlock::~RenderBlock()
{
}

void RenderBlock::SetUpFaces(glm::vec3 position, bool* facesNeeded)
{
    if (facesNeeded[0])  // Top
    {
        m_vertices.push_back(Vertex(glm::vec3(0.5, 0.5, -0.5) + position,
                                  glm::vec4(1, 0, 1, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, -0.5) + position,
                                  glm::vec4(1, 0, 1, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, 0.5) + position,
                                  glm::vec4(1, 0, 1, 1)));
        m_vertices.push_back(
            Vertex(glm::vec3(0.5, 0.5, 0.5) + position, glm::vec4(1, 0, 1, 1)));
        m_size += 4;
    }
    if (facesNeeded[1])  // Down
    {
        m_vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.5) + position,
                                  glm::vec4(0, 1, 0, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.5) + position,
                                  glm::vec4(0, 1, 0, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, -0.5) + position,
                                  glm::vec4(0, 1, 0, 1)));
        m_vertices.push_back(Vertex(glm::vec3(0.5, -0.5, -0.5) + position,
                                  glm::vec4(0, 1, 0, 1)));
        m_size += 4;
    }
    if (facesNeeded[2])  // Left
    {
        m_vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, 0.5) + position,
                                  glm::vec4(1, 1, 0, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, -0.5) + position,
                                  glm::vec4(1, 1, 0, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, -0.5) + position,
                                  glm::vec4(1, 1, 0, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.5) + position,
                                  glm::vec4(1, 1, 0, 1)));
        m_size += 4;
    }
    if (facesNeeded[3])  // Right
    {
        m_vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.5) + position,
                                  glm::vec4(0, 0, 1, 1)));
        m_vertices.push_back(Vertex(glm::vec3(0.5, -0.5, -0.5) + position,
                                  glm::vec4(0, 0, 1, 1)));
        m_vertices.push_back(Vertex(glm::vec3(0.5, 0.5, -0.5) + position,
                                  glm::vec4(0, 0, 1, 1)));
        m_vertices.push_back(
            Vertex(glm::vec3(0.5, 0.5, 0.5) + position, glm::vec4(0, 0, 1, 1)));
        m_size += 4;
    }
    if (facesNeeded[4])  // Front
    {
        m_vertices.push_back(
            Vertex(glm::vec3(0.5, 0.5, 0.5) + position, glm::vec4(0, 1, 1, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, 0.5) + position,
                                  glm::vec4(0, 1, 1, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.5) + position,
                                  glm::vec4(0, 1, 1, 1)));
        m_vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.5) + position,
                                  glm::vec4(0, 1, 1, 1)));
        m_size += 4;
    }
    if (facesNeeded[5])  // Back
    {
        m_vertices.push_back(Vertex(glm::vec3(0.5, -0.5, -0.5) + position,
                                  glm::vec4(1, 0, 0, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, -0.5) + position,
                                  glm::vec4(1, 0, 0, 1)));
        m_vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, -0.5) + position,
                                  glm::vec4(1, 0, 0, 1)));
        m_vertices.push_back(Vertex(glm::vec3(0.5, 0.5, -0.5) + position,
                                  glm::vec4(1, 0, 0, 1)));
        m_size += 4;
    }
}
