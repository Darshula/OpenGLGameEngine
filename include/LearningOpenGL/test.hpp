#ifndef LEARNINGOPENGL_TEST_HPP
#define LEARNINGOPENGL_TEST_HPP

#include <functional>
#include <iostream>
#include <vector>

namespace test {

class Test {
public:
  Test()          = default;
  virtual ~Test() = default;

  virtual void onUpdate(float /*deltaTime*/) {}

  virtual void onRender() {}

  virtual void onImGuiRender() {}

private:
public:
  Test(const Test &)            = delete;
  Test &operator=(const Test &) = delete;
  Test(Test &&)                 = delete;
  Test &operator=(Test &&)      = delete;
};

class TestMenu : public Test {
public:
  explicit TestMenu(Test *&currentTestPointer);
  ~TestMenu() override = default;

  void onImGuiRender() override;

  template <typename T, typename Context>
  void registerTest(const std::string &name, const Context &context) {
    m_Tests.push_back(std::make_pair(name, [&context] { return new T(context); }));
    std::cout << "Registered test " << name << '\n';
  }

private:
  Test *&m_CurrentTest;
  std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;

public:
  TestMenu(const TestMenu &)            = delete;
  TestMenu &operator=(const TestMenu &) = delete;
  TestMenu(TestMenu &&)                 = delete;
  TestMenu &operator=(TestMenu &&)      = delete;
};

} // namespace test

#endif // LEARNINGOPENGL_TEST_HPP
