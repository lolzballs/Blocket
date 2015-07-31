#include "world.h"

World::World() : m_chunk(0, 0)
{
}

World::~World()
{
}

void World::Update(InputHandler input)
{
    if (input.IsKeyDown(SDLK_p))
    {
        for (int i = 0; i < 16; i++)
        {
            m_chunk.AddBlock(1, glm::vec3(i, i, i), true);
        }
    }

    m_chunk.Update();
}

void World::Render()
{
    m_chunk.Render();
}

std::vector<AABB> World::GetBlockAABB(glm::vec3 location)
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
    glm::vec3 min = glm::floor(aabb.GetMin());
    glm::vec3 max = glm::ceil(aabb.GetMax());

    for (int i = min.x; i <= max.x; ++i)
    {
        for (int j = min.y; j <= max.y; ++j)
        {
            for (int k = min.z; k <= max.z; ++k)
            {
                std::vector<AABB> toTest = GetBlockAABB(glm::vec3(i, j, k));
                for (auto& test : toTest)
                {
                    if (test.Intersects(aabb))
                    {
                        m_chunk.AddBlock(
                            0, glm::vec3(i, j, k),
                            true);  // TODO TODO TODO DEBUG CODE PLEASE REMOVE
                        intersecting.push_back(test);
                    }
                }
            }
        }
    }
    return intersecting;
}
