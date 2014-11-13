#include "gamerenderer.h"

GameRenderer::GameRenderer()
{

}

GameRenderer::~GameRenderer()
{

}

void GameRenderer::Input(InputHandler input)
{
	m_world.Input(input);
}

void GameRenderer::Update(float delta)
{
	m_world.Update(delta);
}

void GameRenderer::Render()
{
	m_world.Render();
}
