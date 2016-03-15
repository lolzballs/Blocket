#include "util.h"

namespace Util
{
namespace Texture
{
void LoadTexture(GLuint tex, unsigned char* image, int w, int h, int comp)
{
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
