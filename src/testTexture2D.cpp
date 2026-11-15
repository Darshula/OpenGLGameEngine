#include "LearningOpenGL/indexBuffer.hpp"
#include "LearningOpenGL/renderer.hpp"
#include "LearningOpenGL/shader.hpp"
#include "LearningOpenGL/texture.hpp"
#include "LearningOpenGL/vertexArray.hpp"
#include "LearningOpenGL/vertexBuffer.hpp"
#include "LearningOpenGL/vertexBufferLayout.hpp"
#include "LearningOpenGL/windowContext.hpp"

#include "LearningOpenGL/testTexture2D.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "imgui.h"

#include <array>
#include <memory>

namespace test {
TestTexture2D::TestTexture2D(const WindowContext &context)
    : windowContext(context),
      m_Proj(glm::ortho(0.0F, windowContext.width, 0.0F, windowContext.height,
                        -1.0F, 1.0F)),
      m_View(glm::translate(glm::mat4(1.0F), glm::vec3(0.0F, 0.0F, 0.0F))),
      m_TranslationA(2 * 100.0F, 2 * 100.0F, 0.0F),
      m_TranslationB(4 * 100.0F, 2 * 100.0F, 0.0F) {
  constexpr int coordinatesCount{4 * 4};
  std::array<float, coordinatesCount> positions{
      -100.0 / 2, -100.0 / 2, 0.0, 0.0, 100.0 / 2,  -100.0 / 2, 1.0, 0.0,
      100.0 / 2,  100.0 / 2,  1.0, 1.0, -100.0 / 2, 100.0 / 2,  0.0, 1.0,
  };
  std::array<unsigned int, coordinatesCount> indices{0, 1, 2, 2, 3, 0};

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  m_VertexArray = std::make_unique<VertexArray>();

  m_VertexBuffer = std::make_unique<VertexBuffer>(
      &positions.front(), positions.size() * sizeof(positions.front()));

  VertexBufferLayout layout;
  layout.push<float>(2);
  layout.push<float>(2);

  m_VertexArray->addBuffer(*m_VertexBuffer, layout);
  m_IndexBuffer =
      std::make_unique<IndexBuffer>(&indices.front(), indices.size());

  m_Shader = std::make_unique<Shader>("res/shaders/");
  m_Shader->bind();

  m_Texture = std::make_unique<Texture>("res/textures/Pacman_Open.png");
  m_Shader->setUniform1i("u_Texture", 0);
}

TestTexture2D::~TestTexture2D() = default;

void TestTexture2D::onUpdate(float /*deltaTime*/) {}

void TestTexture2D::onRender() {
  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT);

  m_Texture->bind();

  {
    constexpr int width{1280};
    constexpr int height{720};

    const int incrementTranslation{10};

    if (glfwGetKey(windowContext.window, GLFW_KEY_W) == GLFW_PRESS &&
        static_cast<double>(m_TranslationA.y) < height - (100.0 / 2)) {
      m_TranslationA += glm::vec3{0, incrementTranslation, 0};
    } else if (glfwGetKey(windowContext.window, GLFW_KEY_A) == GLFW_PRESS &&
               static_cast<double>(m_TranslationA.x) > 0 + (100.0 / 2)) {
      m_TranslationA += glm::vec3{-incrementTranslation, 0, 0};
    } else if (glfwGetKey(windowContext.window, GLFW_KEY_S) == GLFW_PRESS &&
               static_cast<double>(m_TranslationA.y) > 0 + (100.0 / 2)) {
      m_TranslationA += glm::vec3{0, -incrementTranslation, 0};
    } else if (glfwGetKey(windowContext.window, GLFW_KEY_D) == GLFW_PRESS &&
               static_cast<double>(m_TranslationA.x) < (width - (100.0 / 2))) {
      m_TranslationA += glm::vec3{incrementTranslation, 0, 0};
    }

    if (glfwGetKey(windowContext.window, GLFW_KEY_UP) == GLFW_PRESS &&
        static_cast<double>(m_TranslationB.y) < height - (100.0 / 2)) {
      m_TranslationB += glm::vec3{0, incrementTranslation, 0};
    } else if (glfwGetKey(windowContext.window, GLFW_KEY_LEFT) == GLFW_PRESS &&
               static_cast<double>(m_TranslationB.x) > 0 + (100.0 / 2)) {
      m_TranslationB += glm::vec3{-incrementTranslation, 0, 0};
    } else if (glfwGetKey(windowContext.window, GLFW_KEY_DOWN) == GLFW_PRESS &&
               static_cast<double>(m_TranslationB.y) > 0 + (100.0 / 2)) {
      m_TranslationB += glm::vec3{0, -incrementTranslation, 0};
    } else if (glfwGetKey(windowContext.window, GLFW_KEY_RIGHT) == GLFW_PRESS &&
               static_cast<double>(m_TranslationB.x) < (width - (100.0 / 2))) {
      m_TranslationB += glm::vec3{incrementTranslation, 0, 0};
    }

    const glm::mat4 model{glm::translate(glm::mat4{1.0F}, m_TranslationA)};
    const glm::mat4 mvp{m_Proj * m_View * model};
    m_Shader->bind();
    m_Shader->setUniformMat4f("u_ModelViewProjectionMatrix", mvp);
    Renderer::draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
  }

  {
    const glm::mat4 model{glm::translate(glm::mat4{1.0F}, m_TranslationB)};
    const glm::mat4 mvp{m_Proj * m_View * model};
    m_Shader->bind();
    m_Shader->setUniformMat4f("u_ModelViewProjectionMatrix", mvp);
    Renderer::draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
  }
}

void TestTexture2D::onImGuiRender() {
  // const float secondsToMilli{1000.0F};
  ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0F,
                      windowContext.width);
  ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0F,
                      windowContext.width);
  ImGui::Text("Move images with WASD and Arrow Keys");
}
} // namespace test
