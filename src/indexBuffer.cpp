#include "LearningOpenGL/indexBuffer.hpp"

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#else
#include "GL/glew.h"
#endif

#include <cstddef>

IndexBuffer::IndexBuffer(const unsigned int *data, int count) : m_Count(count) {
  glGenBuffers(1, &m_RendererID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               static_cast<long>((static_cast<size_t>(count) * sizeof(GLuint))),
               data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_RendererID); }

void IndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
