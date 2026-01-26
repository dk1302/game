#include "app.hpp"
#include "vulkan.hpp"

void App::run() {
  Vulkan vulkan;
  initWindow();
  vulkan.init(window);
  mainLoop();
  vulkan.cleanup();
  cleanup();
}

void App::initWindow() {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Vulkan", nullptr, nullptr);
}

void App::mainLoop() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

void App::cleanup() {
  glfwDestroyWindow(window);

  glfwTerminate();
}
