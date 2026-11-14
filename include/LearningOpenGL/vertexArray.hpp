#ifndef LEARNINGOPENGL_VERTEXARRAY_HPP
#define LEARNINGOPENGL_VERTEXARRAY_HPP

#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

class VertexArray {
public:
  VertexArray();
  ~VertexArray();
  void addBuffer(const VertexBuffer &vertexbuffer,
                 const VertexBufferLayout &layout) const;
  void bind() const;
  static void unbind();

private:
  unsigned int m_RendererID{0};

public:
  VertexArray(const VertexArray &)            = delete;
  VertexArray &operator=(const VertexArray &) = delete;
  VertexArray(VertexArray &&)                 = delete;
  VertexArray &operator=(VertexArray &&)      = delete;
};

#endif // LEARNINGOPENGL_VERTEXARRAY_HPP
