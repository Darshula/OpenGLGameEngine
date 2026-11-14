#ifndef LEARNINGOPENGL_INDEXBUFFER_HPP
#define LEARNINGOPENGL_INDEXBUFFER_HPP

class IndexBuffer {
public:
  IndexBuffer(const unsigned int *data, int count);
  ~IndexBuffer();
  void bind() const;
  static void unbind();

  int getCount() const { return m_Count; }

private:
  unsigned int m_RendererID{0};
  int m_Count;

public:
  IndexBuffer(const IndexBuffer &)            = delete;
  IndexBuffer &operator=(const IndexBuffer &) = delete;
  IndexBuffer(IndexBuffer &&)                 = delete;
  IndexBuffer &operator=(IndexBuffer &&)      = delete;
};

#endif // LEARNINGOPENGL_INDEXBUFFER_HPP
