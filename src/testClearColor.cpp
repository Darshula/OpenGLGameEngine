#include "LearningOpenGL/testClearColor.hpp"
#include "LearningOpenGL/windowContext.hpp"

#include "imgui.h"

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#else
#include "GL/glew.h"
#endif

namespace test {
TestClearColor::TestClearColor(const WindowContext & /*context*/)
    : m_ClearColor{0.0F / RGB, 100.0F / RGB, 186.0F / RGB, 1.0F} {}

TestClearColor::~TestClearColor() = default;

void TestClearColor::onUpdate(float /*deltaTime*/) {}

void TestClearColor::onRender() {
  glClearColor(m_ClearColor.at(0), m_ClearColor.at(1), m_ClearColor.at(2),
               m_ClearColor.at(3));
  glClear(GL_COLOR_BUFFER_BIT);
}

void TestClearColor::onImGuiRender() {
  ImGui::ColorEdit4("Clear Color", &m_ClearColor.at(0));
}

} // namespace test
