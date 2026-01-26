#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer {
public:
  Renderer();
  void run();
  void cleanup();

private:
  unsigned int VAO, VBO, EBO;
  unsigned char *textureData;
  unsigned int texture1, texture2;
  unsigned int shaderID;
  glm::mat4 transform;
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 projection;

  void setupTextures();
  void useTextures();

  void setupShader(const char *vertexPath, const char *fragmentPath);
  void useShader();
  void checkShaderCompileErrors(unsigned int shader, std::string type);

  void useTransformations();

  void useCamera();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec2(const std::string &name, const glm::vec2 &value) const;
  void setVec2(const std::string &name, float x, float y) const;
  void setVec3(const std::string &name, const glm::vec3 &value) const;
  void setVec3(const std::string &name, float x, float y, float z) const;
  void setVec4(const std::string &name, const glm::vec4 &value) const;
  void setVec4(const std::string &name, float x, float y, float z, float w) const;
  void setMat2(const std::string &name, const glm::mat2 &mat) const;
  void setMat3(const std::string &name, const glm::mat3 &mat) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

  void draw();
};
