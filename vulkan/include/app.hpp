#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const uint32_t SCR_WIDTH = 800;
const uint32_t SCR_HEIGHT = 600;

class App {
public:
  void run();

private:
  GLFWwindow *window;

  void initWindow();

  void mainLoop();

  void cleanup();
};
