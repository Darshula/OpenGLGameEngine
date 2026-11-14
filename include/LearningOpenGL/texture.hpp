#ifndef LEARNINGOPENGL_TEXTURE_HPP
#define LEARNINGOPENGL_TEXTURE_HPP

#include <string>

class Texture {
public:
  explicit Texture(std::string path);
  ~Texture();
  void bind(unsigned int slot = 0) const;
  static void unbind();

  int getWidth() const { return m_Width; }

  int getHeight() const { return m_Height; }

private:
  unsigned int m_RendererID{0};
  std::string m_Filepath;
  unsigned char *m_LocalBuffer{nullptr};
  int m_Width{0};
  int m_Height{0};
  int m_BytesPerPixel{0};

public:
  Texture(const Texture &)            = delete;
  Texture &operator=(const Texture &) = delete;
  Texture(Texture &&)                 = delete;
  Texture &operator=(Texture &&)      = delete;
};

#endif // LEARNINGOPENGL_TEXTURE_HPP
