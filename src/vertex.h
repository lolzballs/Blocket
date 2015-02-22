#ifndef VERTEX_H
#define VERTEX_H

#define VERTEX_SIZE 9

#include <glm/glm.hpp>

class Vertex {
public:
    Vertex(glm::vec3 position);

    Vertex(glm::vec3 position, glm::vec4 color);

    Vertex(glm::vec3 position, glm::vec2 texCoord);

    Vertex(glm::vec3 position, glm::vec2 texCoord, glm::vec4 color);

    ~Vertex();

    static float *GetFloatArray(Vertex *vertices, unsigned int size);

    inline glm::vec3 GetPosition() {
        return m_position;
    }

    inline glm::vec4 GetColor() {
        return m_color;
    }

    inline glm::vec2 GetTexCoord() {
        return m_texCoord;
    }

private:
    glm::vec3 m_position;
    glm::vec4 m_color;
    glm::vec2 m_texCoord;
};

#endif // VERTEX_H
