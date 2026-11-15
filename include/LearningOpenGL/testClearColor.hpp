#ifndef LEARNINGOPENGL_TESTCLEARCOLOR_HPP
#define LEARNINGOPENGL_TESTCLEARCOLOR_HPP

#include "test.hpp"

#include <array>

struct WindowContext;

namespace test {
class TestClearColor : public Test {
public:
  TestClearColor(const WindowContext & /*context*/);
  ~TestClearColor() override;

  void onUpdate(float deltaTime) override;
  void onRender() override;
  void onImGuiRender() override;

private:
  const float RGB{255.0F};
  std::array<float, 4> m_ClearColor;

public:
  TestClearColor(const TestClearColor &)            = delete;
  TestClearColor &operator=(const TestClearColor &) = delete;
  TestClearColor(TestClearColor &&)                 = delete;
  TestClearColor &operator=(TestClearColor &&)      = delete;
};
} // namespace test

#endif // LEARNINGOPENGL_TESTCLEARCOLOR_HPP
