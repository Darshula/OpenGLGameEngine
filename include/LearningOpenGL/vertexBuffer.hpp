#ifndef LEARNINGOPENGL_VERTEXBUFFER_HPP
#define LEARNINGOPENGL_VERTEXBUFFER_HPP

class VertexBuffer {
public:
  VertexBuffer(const void *data, unsigned int size);
  ~VertexBuffer();
  void bind() const;
  static void unbind();

private:
  unsigned int m_RendererID{0};

public:
  VertexBuffer(const VertexBuffer &)            = delete;
  VertexBuffer &operator=(const VertexBuffer &) = delete;
  VertexBuffer(VertexBuffer &&)                 = delete;
  VertexBuffer &operator=(VertexBuffer &&)      = delete;
};

#endif // LEARNINGOPENGL_VERTEXBUFFER_HPP
