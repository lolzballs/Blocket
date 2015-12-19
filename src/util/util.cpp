#include "util.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Util
{
namespace Texture
{
int LoadTexture(std::string filepath)
{
	int w;
	int h;
	int comp;
	unsigned char* image = stbi_load(filepath.c_str(), &w, &h, &comp, STBI_rgb_alpha);

	if (image == nullptr)
	{
		throw(std::string("Failed to load texture: " + filepath));
	}

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (comp == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else if (comp == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image);

    return tex;
}
}

namespace Vector
{
glm::vec3 Lerp(glm::vec3 a, glm::vec3 b, float n)
{
    return a + (b - a) * n;
}

glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float n)
{
    return a + (b - a) * n;
}
}
}
