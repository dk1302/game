#include "renderer.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// #include <GLFW/glfw3.h>

Renderer::Renderer() {
  setupTextures();

  setupShader("src/shaders/vert.glsl", "src/shaders/frag.glsl");

  glEnable(GL_DEPTH_TEST);

  // Buffer setup
  float vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)0); // Vertex attributes stay the same
  glEnableVertexAttribArray(0);
  // Texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void Renderer::run() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  useTextures();
  useShader();
  useTransformations();
  useCamera();
  draw();

  // glBindVertexArray(VAO);
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  // glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::draw() {
  glm::vec3 objPositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  glBindVertexArray(VAO);
  for(unsigned int i = 0; i < 10; i++)
  {
      model = glm::mat4(1.0f);
      model = glm::translate(model, objPositions[i]);
      float angle = 20.0f * i; 
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
  }
}

void Renderer::useTransformations() {
  transform = glm::mat4(1.0f);
  // transform =
  //     glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
  // transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));
  setMat4("transform", transform);
}

void Renderer::useCamera() {
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); 
  projection =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  setMat4("projection", projection);
}

void Renderer::setupTextures() {

  int width, height, nrChannels;

  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);

  textureData =
      stbi_load("images/container.jpg", &width, &height, &nrChannels, 0);
  if (!textureData) {
    std::cout << "Failed to load texture" << std::endl;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(textureData);

  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);

  stbi_set_flip_vertically_on_load(true);

  textureData =
      stbi_load("images/awesomeface.png", &width, &height, &nrChannels, 0);
  if (!textureData) {
    std::cout << "Failed to load texture" << std::endl;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(textureData);
}

void Renderer::useTextures() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);
}

void Renderer::setupShader(const char *vertexPath, const char *fragmentPath) {
  // 1. retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure &e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what()
              << std::endl;
  }
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  // 2. compile shaders
  unsigned int vertex, fragment;
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  checkShaderCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  checkShaderCompileErrors(fragment, "FRAGMENT");
  // shader Program
  shaderID = glCreateProgram();
  glAttachShader(shaderID, vertex);
  glAttachShader(shaderID, fragment);
  glLinkProgram(shaderID);
  checkShaderCompileErrors(shaderID, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer
  // necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  useShader();
  setInt("texture1", 0);
  setInt("texture2", 1);
}
// activate the shader
// ------------------------------------------------------------------------
void Renderer::useShader() { glUseProgram(shaderID); }
// utility uniform functions
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
void Renderer::checkShaderCompileErrors(unsigned int shader, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  }
}

void Renderer::cleanup() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void Renderer::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Renderer::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Renderer::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Renderer::setVec2(const std::string &name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}
void Renderer::setVec2(const std::string &name, float x, float y) const {
  glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Renderer::setVec3(const std::string &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}
void Renderer::setVec3(const std::string &name, float x, float y,
                       float z) const {
  glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Renderer::setVec4(const std::string &name, const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}
void Renderer::setVec4(const std::string &name, float x, float y, float z,
                       float w) const {
  glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Renderer::setMat2(const std::string &name, const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
// ------------------------------------------------------------------------
void Renderer::setMat3(const std::string &name, const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
// ------------------------------------------------------------------------
void Renderer::setMat4(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
