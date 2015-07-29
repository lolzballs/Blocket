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
