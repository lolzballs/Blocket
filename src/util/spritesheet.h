#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <string>
#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Spritesheet
{
public:
    Spritesheet(std::string file, int size);
    ~Spritesheet();

    void BindTexture();
    std::array<glm::vec2, 2> GetTexCoords(int i);
private:
    GLuint m_tex;
    int m_size;
    int m_length;
    int m_numsprites;
};

#endif
