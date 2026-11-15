#version 300 es

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_ModelViewProjectionMatrix;

void main() {
  gl_Position = u_ModelViewProjectionMatrix * position;
  v_TexCoord  = texCoord;
}
