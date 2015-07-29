#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "world/world.h"
#include "basicshader.h"
#include "player.h"

class GameRenderer
{
public:
    GameRenderer(float fov, float aspect, float zNear, float zFar);
    ~GameRenderer();

    void Input(InputHandler input);
    void Update();
    void Render(float delta);

    inline const World GetWorld()
    {
        return m_world;
    }

private:
    BasicShader m_shader;
    World m_world;
    Player m_player;
    glm::mat4 m_perspective;
    glm::mat4 m_transformation;
};

#endif
