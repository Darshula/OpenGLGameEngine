#include "LearningOpenGL/renderer.hpp"

#include "LearningOpenGL/test.hpp"
#include "LearningOpenGL/testClearColor.hpp"
#include "LearningOpenGL/testTexture2D.hpp"
#include "LearningOpenGL/windowContext.hpp"

#ifdef __EMSCRIPTEN__
#  include <GLES3/gl3.h>
#  include <emscripten.h>
#else
#  include "GL/glew.h"
#endif

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

int main(int /*argc*/, char ** /*argv*/) {

  static WindowContext windowContext{};
  if (glfwInit() != GLFW_TRUE) {
    return -1;
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
#ifdef __EMSCRIPTEN__
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  windowContext.window = glfwCreateWindow(
      static_cast<int>(windowContext.width),
      static_cast<int>(windowContext.height), "Hello World", nullptr, nullptr);
  if (windowContext.window == nullptr) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(windowContext.window);
#ifndef __EMSCRIPTEN__
  glewExperimental = GL_TRUE;
  const GLenum glewStatus = glewInit();
  if (glewStatus != GLEW_OK) {
    std::cerr << "GLEW initialization failed: "
              << reinterpret_cast<const char *>(glewGetErrorString(glewStatus))
              << '\n';
    glfwDestroyWindow(windowContext.window);
    glfwTerminate();
    return -1;
  }
#endif

  glfwSwapInterval(1);

  std::cout << "OpenGL renderer " << glGetString(GL_RENDERER) << '\n'
            << "OpenGL version " << glGetString(GL_VERSION) << '\n'
            << "GLSL version " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << '\n';

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(windowContext.window, true);
#ifdef __EMSCRIPTEN__
  ImGui_ImplOpenGL3_Init("#version 300 es");
#else
  ImGui_ImplOpenGL3_Init("#version 330 core");
#endif
  ImGui::StyleColorsDark();

  static test::Test *currentTest{nullptr};
  static auto *testMenu = new test::TestMenu(currentTest);
  currentTest           = testMenu;

  testMenu->registerTest<test::TestClearColor>("Clear Color", windowContext);
  testMenu->registerTest<test::TestTexture2D>("2D Texture", windowContext);

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(
      [] {
#else
  while (glfwWindowShouldClose(windowContext.window) == GLFW_FALSE) {
#endif
        glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
        Renderer::clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest != nullptr) {
          currentTest->onUpdate(0.0F);
          currentTest->onRender();
          ImGui::Begin("Tests Window");
          ImGui::Text("%.1f FPS",
                      static_cast<double>(ImGui::GetIO().Framerate));
          if (currentTest != testMenu && ImGui::Button("<- Back")) {
            delete currentTest;
            currentTest = testMenu;
          }
          currentTest->onImGuiRender();
          ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(windowContext.window);
        glfwPollEvents();
#ifdef __EMSCRIPTEN__
      },
      0, true);
#else
  }
  if (currentTest != testMenu) {
    delete currentTest;
  }
  delete testMenu;
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(windowContext.window);
  glfwTerminate();
#endif
  return 0;
}
