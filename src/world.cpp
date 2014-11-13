#include "world.h"

World::World()
	: m_chunk(0, 0)
{

}

World::~World()
{

}

void World::Input(InputHandler input)
{

}

void World::Update(float delta)
{
    m_chunk.Update(delta);
}

void World::Render()
{
    m_chunk.Render();
}

