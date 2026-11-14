#ifndef LEARNINGOPENGL_SHADER_HPP
#define LEARNINGOPENGL_SHADER_HPP

#include <glm/ext/matrix_float4x4.hpp>
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
  std::string vertexSource;
  std::string fragmentSource;
};

class Shader {
private:
  static ShaderProgramSource parseShader(const std::string &fileDirectory);
  static unsigned int compileShader(unsigned int type,
                                    const std::string &source);
  static unsigned int createShader(const std::string &vertexShader,
                                   const std::string &fragmentShader);
  int getUniformLocation(const std::string &name);

public:
  explicit Shader(std::string fileDirectory);
  ~Shader();
  void bind() const;
  static void unbind();
  void setUniform1i(const std::string &name, int value);
  void setUniform1f(const std::string &name, float value);
  void setUniform4f(const std::string &name, float value0, float value1,
                    float value2, float value3);
  void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);

private:
  unsigned int m_RendererID{0};
  std::string m_FileDirectory;
  std::unordered_map<std::string, int> m_UniformLocationCache;

public:
  Shader(const Shader &)            = delete;
  Shader &operator=(const Shader &) = delete;
  Shader(Shader &&)                 = delete;
  Shader &operator=(Shader &&)      = delete;
};

#endif // LEARNINGOPENGL_SHADER_HPP
