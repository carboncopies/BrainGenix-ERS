#include "bgfx/bgfx.h"
#include "GLFW/glfw3.h"

#define WNDW_WIDTH 1600
#define WNDW_HEIGHT 900

int main(void)
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WNDW_WIDTH, WNDW_HEIGHT, "Hello, bgfx!", NULL, NULL);
    bgfx::init();
    return 0;
}