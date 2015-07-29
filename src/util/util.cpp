#include "util.h"

namespace Util
{
namespace Texture
{
int LoadTexture(std::string filepath)
{
    return 100;
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
