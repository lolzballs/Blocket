#ifndef UTIL_H
#define UTIL_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

namespace Util
{
namespace Texture
{
int LoadTexture(std::string filepath);
}

namespace Vector
{
glm::vec3 Lerp(glm::vec3 a, glm::vec3 b, float n);
glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float n);
}
}

#endif
