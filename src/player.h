#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
    Player(World& world, glm::vec3 position, glm::vec2 rotation, float speed);
    ~Player();

    void Update(InputHandler& input) override;
    void Render(float delta) override;

    glm::vec3 GetPlayerRenderPosition(float delta);
private:
    GLuint m_vbo;
    AABB m_blockSelected;

    void InitGL();
    void BufferBoundingBox(float delta);
};

#endif
