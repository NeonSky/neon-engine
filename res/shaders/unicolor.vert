#version 420

uniform mat4 model_view_projection;
uniform vec3 color;

layout(location = 0) in vec3 position;

out vec3 outColor;

void main() {
  gl_Position = model_view_projection * vec4(position, 1.0);
  outColor = color;
}
