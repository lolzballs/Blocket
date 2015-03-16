#include <thread>
#include "gamerenderer.h"

GameRenderer::GameRenderer(float fov, float aspect, float zNear, float zFar)
        : m_perspective(glm::perspective(glm::radians(fov), aspect, zNear, zFar)) {
}

GameRenderer::~GameRenderer() {

}

bool first = true;
time_t start;

void GameRenderer::Input(InputHandler input) {
    glm::vec2 mouseDelta = input.GetMousePosition();

    m_rotation += glm::vec2(mouseDelta.y, -mouseDelta.x);

    if (m_rotation.x > 90) {
        m_rotation.x = 90;
    }
    else if (m_rotation.x < -90) {
        m_rotation.x = -90;
    }

    if (input.IsKeyDown(SDLK_w)) {
//        m_movement += glm::vec3(cos(glm::radians(m_rotation.y - 90)), 0, sin(glm::radians(m_rotation.y - 90)));
        m_movement += glm::vec3(1, 0, 0);
    }
    if (input.IsKeyDown(SDLK_s)) {
//        m_movement -= glm::vec3(cos(glm::radians(m_rotation.y - 90)), 0, sin(glm::radians(m_rotation.y - 90)));
        m_movement -= glm::vec3(1, 0, 0);
    }
    if (input.IsKeyDown(SDLK_a)) {
//        m_movement -= glm::vec3(cos(glm::radians(m_rotation.y)), 0, sin(glm::radians(m_rotation.y)));
        if (first) {
            first = false;
            start = SDL_GetTicks();
        }
        m_movement -= glm::vec3(0, 0, 1);
    }
    if (input.IsKeyDown(SDLK_d)) {
//        m_movement += glm::vec3(cos(glm::radians(m_rotation.y)), 0, sin(glm::radians(m_rotation.y)));
        m_movement += glm::vec3(0, 0, 1);
    }
    if (input.IsKeyDown(SDLK_SPACE)) {
        m_movement += glm::vec3(0, 1, 0);
    }

    m_world.Input(input);
}

void GameRenderer::Update() {
    m_world.Update();

    if (m_movement != glm::vec3()) {
        m_velocity += glm::normalize(m_movement);
        m_movement = glm::vec3();
    }

    m_position += m_velocity * 0.1f;
    m_velocity *= 0.1f;
}

void GameRenderer::Render(float delta) {
    if (m_position.z >= 10.0f) {
        std::cout << SDL_GetTicks() - start << std::endl;
    }

    glm::vec2 rotation = glm::radians(m_rotation);
    m_transformation = glm::translate(glm::eulerAngleXY(rotation.x, rotation.y), -(m_position + m_velocity * 0.1f * delta));
    m_shader.UpdateUniforms(m_perspective * m_transformation);

    m_world.Render();
}


