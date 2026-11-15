#ifndef LEARNINGOPENGL_VERTEXBUFFERLAYOUT_HPP
#define LEARNINGOPENGL_VERTEXBUFFERLAYOUT_HPP

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#else
#include "GL/glew.h"
#endif

#include <vector>

struct VertexBufferElement {
  GLenum type;
  int count;
  GLboolean normalized;

  static int getTypeSize(GLenum type) {
    switch (type) {
    case GL_FLOAT:
      return sizeof(float);
    case GL_UNSIGNED_INT:
      return sizeof(unsigned int);
    case GL_UNSIGNED_BYTE:
      return sizeof(unsigned char);
    default:
      return 0;
    }
  }
};

class VertexBufferLayout {
public:
  VertexBufferLayout()  = default;
  ~VertexBufferLayout() = default;
  template <typename T> void push(int count);

  int getStride() const { return m_Stride; }

  const std::vector<VertexBufferElement> &getElements() const {
    return m_Elements;
  }

private:
  std::vector<VertexBufferElement> m_Elements;
  int m_Stride{};

public:
  VertexBufferLayout(const VertexBufferLayout &)            = delete;
  VertexBufferLayout &operator=(const VertexBufferLayout &) = delete;
  VertexBufferLayout(VertexBufferLayout &&)                 = delete;
  VertexBufferLayout &operator=(VertexBufferLayout &&)      = delete;
};

template <> inline void VertexBufferLayout::push<float>(int count) {
  m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
  m_Stride += count * VertexBufferElement::getTypeSize(GL_FLOAT);
}

template <>
inline void VertexBufferLayout::push<unsigned int>(int count) {
  m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_Stride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_INT);
}

template <>
inline void VertexBufferLayout::push<unsigned char>(int count) {
  m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
  m_Stride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_BYTE);
}

#endif // LEARNINGOPENGL_VERTEXBUFFERLAYOUT_HPP
