#include "game.h"

Game::Game()
    : m_updateTime(1000.0f / 20.0f),
      m_width(800),
      m_height(640),
      m_title("Blocket"),
      m_window(m_width, m_height, m_title),
      m_gameRenderer(70.0f, (float)m_width / (float)m_height, 0.01f, 1000.0f),
      m_running(false)
{
    std::cout << "Game initalized." << std::endl;
}

Game::~Game()
{
}

void Game::Start()
{
    std::cout << "Starting game..." << std::endl;

    m_running = true;
    InitGL();

    Run();
}

void Game::Stop()
{
    std::cout << "Stopping game..." << std::endl;
    m_running = false;
}

void Game::Run()
{
    Uint32 lastTime = SDL_GetTicks();

    int frames = 0;
    int updates = 0;

    Uint32 lastTimer = SDL_GetTicks();
    float delta = 0;
    float lastTick = 0;
    float renderDelta = 0;

    while (m_running)
    {
        Uint32 now = SDL_GetTicks();
        delta += (now - lastTime) / m_updateTime;
        lastTime = now;

        Input(m_window.GetInput());

        // Update if needed
        while (delta >= 1.0f)
        {
            updates++;
            lastTick = SDL_GetTicks();
            Update();
            Input(m_window.GetInput());
            delta -= 1.0f;
        }

        renderDelta = (SDL_GetTicks() - lastTick) / m_updateTime;

        // Render cycle
        frames++;
        Render(renderDelta);
        m_window.Update();

        if (SDL_GetTicks() - lastTimer >= 1000)
        {
            lastTimer += 1000;
            std::cout << updates << " TPS, " << frames << " FPS" << std::endl;
            frames = 0;
            updates = 0;
        }
    }
}

// Function to separate OpenGL initialization things
void Game::InitGL()
{
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0, 0, 0, 1);
}

// Handle inputs, called every frame
void Game::Input(InputHandler input)
{
    if (input.IsKeyDown(SDLK_ESCAPE) || m_window.IsCloseRequested())
    {
        Stop();
    }

    m_gameRenderer.Input(input);
    m_hud.Input(input);
}

// Game logic (movement, etc.)
void Game::Update()
{
    m_gameRenderer.Update();
    m_hud.Update();
}

// Render!
void Game::Render(float delta)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_gameRenderer.Render(delta);

    // Render afterwards to overlay
    m_hud.InitOrtho(m_width, m_height, -0.1f, 1000.0f);
    m_hud.Render();
}
