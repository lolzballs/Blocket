#include "hud.h"

#include <glad/glad.h>

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::Update(InputHandler& input)
{
}

void HUD::Render()
{
    glUseProgram(0);  // Disables shaders
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glBegin(GL_TRIANGLES);
    {
        glColor3f(1, 1, 1);
        glVertex2f(0, 0);
        glColor3f(1, 0, 1);
        glVertex2f(100, 0);
        glColor3f(1, 0, 0);
        glVertex2f(100, 100);
    }
    glEnd();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void HUD::InitOrtho(int width, int height, float zNear, float zFar)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, height, 0, zNear, zFar);
}
