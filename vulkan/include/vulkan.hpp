#include <vector>
#include <vulkan/vulkan.h>

#include <cstdlib>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif



struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  bool isComplete() { return graphicsFamily.has_value(); }
};

class Vulkan {
public:
  void init(GLFWwindow *window);
  void cleanup();

private:
  VkInstance instance;
  VkDevice device;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkQueue graphicsQueue;
  VkSurfaceKHR surface;

  void createInstance();
  void createSurface(GLFWwindow *window);
  void pickPhysicalDevice();
  void createLogicalDevice();
  bool checkValidationLayerSupport();
  bool isDeviceSuitable(VkPhysicalDevice device);
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

};
