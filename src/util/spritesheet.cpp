#include "spritesheet.h"
#include "util/util.h"

#include <iostream>
#include <array>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Spritesheet::Spritesheet(std::string file, int size)
    : m_size(size)
{
    int comp, w, h;
    unsigned char* image = stbi_load(file.c_str(), &w, &h, &comp, STBI_rgb_alpha);

    if (image == nullptr)
    {
        std::cerr << "Failed to load spritesheet: " << file << std::endl;
        abort();
    }

    if (w != h || w % size != 0)
    {
        std::cerr << "Spritesheet sizes do not match up!" << std::endl;
        abort();
    }

    glGenTextures(1, &m_tex);
    Util::Texture::LoadTexture(m_tex, image, w, h, comp);

    m_length = w;
    m_numsprites = m_length / size;

    stbi_image_free(image);
}


Spritesheet::~Spritesheet()
{
    glDeleteTextures(1, &m_tex);
}

void Spritesheet::BindTexture()
{
    glBindTexture(GL_TEXTURE_2D, m_tex);
}


std::array<glm::vec2, 2> Spritesheet::GetTexCoords(int i)
{
    int minx = i % m_numsprites - 1;
    int miny = std::max(0, i / m_numsprites - 1);
    int maxx = i % m_numsprites;
    int maxy = i / m_numsprites + 1;
    return{ { { (float)minx / m_numsprites, (float)miny / m_numsprites },{ (float)maxx / m_numsprites, (float)maxy / m_numsprites } } };
}
