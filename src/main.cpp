#undef max
#undef min

#include "game.h"

int main()
{
	glfwInit();
    Game().Start();
	glfwTerminate();
    return 0;
}
