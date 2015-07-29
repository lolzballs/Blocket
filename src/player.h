#ifndef PLAYER_H
#define PLAYER_H

#include "input.h"

#include <glm/glm.hpp>

class Player
{
public:
    Player(glm::vec3 position);
    ~Player();

    void Input(InputHandler input);
    void Update();
    void Render(float delta);

    glm::vec3 GetRenderPosition(float delta);
    glm::vec2 GetRenderRotation(); // TODO: Add delta to rotation
private:
    glm::vec3 m_position;
    glm::vec3 m_oldposition;
    glm::vec3 m_movement;
    glm::vec3 m_velocity;
    glm::vec2 m_rotation;
};

#endif
