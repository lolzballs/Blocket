#ifndef CHUNK_H
#define CHUNK_H

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include "block.h"

#define CHUNK_HEIGHT 256

class Chunk
{
public:
	Chunk(int x, int y);
	virtual ~Chunk();

	void Render();
	void Update(float delta);
	void AddBlock(int blockID, glm::vec3 position);
	Block GetBlockAtPosition(glm::vec3 position);

	inline const glm::vec2 GetPosition() { return m_position; }
private:
	glm::vec2 m_position;
	std::vector<Block> m_blocks;
	int m_vbo;
	int m_ibo;

    bool* GetFacesRequired(glm::vec3 position);
    void RebufferChunk();
};

#endif
