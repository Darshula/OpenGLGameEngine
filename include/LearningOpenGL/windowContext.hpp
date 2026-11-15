#ifndef LEARNINGOPENGL_WINDOWCONTEXT_HPP
#define LEARNINGOPENGL_WINDOWCONTEXT_HPP

struct GLFWwindow;

struct WindowContext {
  GLFWwindow *window = nullptr;
  float width        = 1280;
  float height       = 720;
};

#endif // LEARNINGOPENGL_WINDOWCONTEXT_HPP
