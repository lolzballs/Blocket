#include "game.h"

#include <glad/glad.h>

#include <iostream>

Game::Game()
    : m_updateTime(1000.0f / 20.0f),
      m_width(800),
      m_height(640),
      m_title("Blocket"),
      m_window(m_width, m_height, m_title),
      m_gameRenderer(70.0f, float(m_width) / float(m_height), 0.01f, 1000.0f),
      m_running(false)
{
	GLFWwindow* window = m_window.GetGLFWWindow();

	glfwSetCursorPosCallback(window, &InputHandler::MousePositionCallback);
	glfwSetMouseButtonCallback(window, &InputHandler::MouseButtonCallback);
	glfwSetScrollCallback(window, &InputHandler::MouseWheelCallback);
	glfwSetKeyCallback(window, &InputHandler::KeyCallback);

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
    double lastTime = glfwGetTime();

    int frames = 0;
    int updates = 0;

    double lastTimer = glfwGetTime();
    float delta = 0;
    float lastTick = 0;
    float renderDelta = 0;

    while (m_running)
    {
        int now = glfwGetTime() * 1000;
        delta += (now - lastTime) / m_updateTime;
        lastTime = now;

        // Update if needed
        while (delta >= 1.0f)
        {
            updates++;
            lastTick = glfwGetTime() * 1000;
            Update();
            delta -= 1.0f;
        }

        renderDelta = (glfwGetTime() * 1000 - lastTick) / m_updateTime;

        // Render cycle
        frames++;
        Render(renderDelta);
        m_window.Update();

        if (glfwGetTime() * 1000 - lastTimer >= 1000)
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

// Game logic (movement, etc.)
void Game::Update()
{
	auto& input = InputHandler::GetInstance();
    if (m_window.IsCloseRequested())
    {
        Stop();
    }

	if (input.IsKeyDown(GLFW_KEY_ESCAPE))
	{
		glfwSetInputMode(m_window.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

    m_gameRenderer.Update(input);
    m_hud.Update(input);
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
