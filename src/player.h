#ifndef PLAYER_H
#define PLAYER_H

#include "input.h"
#include "util/cside.h"
#include "world/world.h"

#include <queue>

class Player
{
public:
    Player(glm::vec2 rotation, glm::vec3 position, float speed, World* world);
    ~Player();

    void Update(InputHandler input);
    void Render(float delta);

    glm::vec3 GetRenderPosition(float delta);
    glm::vec2 GetRenderRotation(float delta);
private:
    AABB m_aabb;
    glm::vec2 m_rotation;
    glm::vec2 m_oldrotation;
    glm::vec3 m_position;
    glm::vec3 m_oldposition;
    glm::vec3 m_velocity;
    float m_speed;
    World* m_world;
    GLuint m_vbo;

    void InitGL();
    void BufferBoundingBox(float delta);
};

#endif
