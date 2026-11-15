#include "LearningOpenGL/renderer.hpp"
#include "LearningOpenGL/indexBuffer.hpp"
#include "LearningOpenGL/shader.hpp"
#include "LearningOpenGL/vertexArray.hpp"

#ifdef __EMSCRIPTEN__
#  include <GLES3/gl3.h>
#else
#  include "GL/glew.h"
#endif

void Renderer::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::draw(const VertexArray &var, const IndexBuffer &ibx,
                    const Shader &shader) {

  shader.bind();
  var.bind();
  glDrawElements(GL_TRIANGLES, ibx.getCount(), GL_UNSIGNED_INT, nullptr);
}
