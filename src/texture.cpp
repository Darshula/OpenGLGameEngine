#include "LearningOpenGL/texture.hpp"

#include "stb/stb_image.h"

#ifdef __EMSCRIPTEN__
#  include <GLES3/gl3.h>
#else
#  include "GL/glew.h"
#endif

#include <stdexcept>
#include <string>
#include <utility>

Texture::Texture(std::string path) : m_Filepath(std::move(path)) {
  stbi_set_flip_vertically_on_load(1);
  m_LocalBuffer =
      stbi_load(m_Filepath.c_str(), &m_Width, &m_Height, &m_BytesPerPixel, 4);

  glGenTextures(1, &m_RendererID);
  glBindTexture(GL_TEXTURE_2D, m_RendererID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, m_LocalBuffer);
  glBindTexture(GL_TEXTURE_2D, 0);

  if (m_LocalBuffer != nullptr) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, m_LocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(m_LocalBuffer);
  } else {
    throw std::runtime_error("[ERROR]: Failed to load texture '" + m_Filepath +
                             "'");
  }
}

Texture::~Texture() { glDeleteTextures(1, &m_RendererID); }

void Texture::bind(unsigned int slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
