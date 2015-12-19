#include "world.h"

World::World() : m_chunk(0, 0)
{
}

World::~World()
{
}

void World::Update(InputHandler& input)
{
    if (input.IsKeyDown(GLFW_KEY_P))
    {
        for (int i = 0; i < 16; i++)
        {
            m_chunk.AddBlock(1, glm::vec3(i, i, i));
        }
    }

    m_chunk.Update();
}

void World::Render(BasicShader& shader)
{
    m_chunk.Render(shader);
}

std::vector<AABB> World::GetBlockAABBs(glm::vec3 location)
{
    std::vector<AABB> aabbs;
    if (m_chunk.GetBlockAtPosition(location) != 0)
    {
        aabbs.push_back(AABB(location, glm::vec3(-0.5, -0.5, -0.5),
                             glm::vec3(0.5, 0.5, 0.5)));
    }
    return aabbs;
}

std::vector<AABB> World::GetIntersectingAABBs(AABB aabb)
{
    std::vector<AABB> intersecting;
    glm::vec3 min = glm::floor(aabb.GetAbsMin());
    glm::vec3 max = glm::ceil(aabb.GetAbsMax());

    for (int i = min.x; i <= max.x; i++)
    {
        for (int j = min.y; j <= max.y; j++)
        {
            for (int k = min.z; k <= max.z; k++)
            {
                std::vector<AABB> toTest = GetBlockAABBs(glm::vec3(i, j, k));
                for (auto& test : toTest)
                {
                    if (test.Intersects(aabb))
                    {
                        intersecting.push_back(test);
                    }
                }
            }
        }
    }
    return intersecting;
}
