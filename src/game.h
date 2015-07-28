#ifndef GAME_H
#define GAME_H

#include "basicshader.h"
#include "window.h"
#include "hud.h"
#include "gamerenderer.h"

class Game
{
public:
    Game();

    virtual ~Game();

    void Start();
    void Stop();

private:
    const float m_updateTime;
    const int m_width;
    const int m_height;
    const std::string m_title;

    Window m_window;
    HUD m_hud;
    GameRenderer m_gameRenderer;
    bool m_running;

    void Run();
    void InitGL();
    void Input(InputHandler input);
    void Update();
    void Render(float delta);
};

#endif
