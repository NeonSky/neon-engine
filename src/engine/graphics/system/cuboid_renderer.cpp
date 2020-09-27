#include "cuboid_renderer.hpp"

#include "../component/global_transform.hpp"
#include "../component/render_info.hpp"

using namespace engine::graphics::system;

CuboidRenderer::CuboidRenderer()
        : _shader(Shader("unicolor.vert", "color.frag")) {}

void CuboidRenderer::update(architecture::ECS& ecs) {
  CHECK_GL_ERROR();

  auto& render_info = ecs.get<component::RenderInfo>(ecs.view<component::RenderInfo>()[0]);
  auto& ctx         = render_info.context.get();

  _shader.use();

  for (auto entity : ecs.view<component::Cuboid>()) {
    auto& cuboid = ecs.get<component::Cuboid>(entity);

    if (cuboid.vao == 0)
      compile_cuboid(ctx, cuboid);

    glBindVertexArray(ctx.vao(cuboid.vao));

    glBindBuffer(GL_ARRAY_BUFFER, cuboid.vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0U, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cuboid.ibo);

    auto mvp = render_info.view_projection * ecs.get<component::GlobalTransform>(entity).matrix;
    _shader.set_uniform_rgb("color", cuboid.color);
    _shader.set_uniform_mat4("model_view_projection", mvp);

    glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr);
    if (_draw_corners) {
      glPointSize(10.0F);
      glDrawElements(GL_POINTS, 3 * 12, GL_UNSIGNED_INT, nullptr);
    }
  }

  glBindVertexArray(0);
  CHECK_GL_ERROR();
}

void CuboidRenderer::compile_cuboid(opengl::Context& ctx, component::Cuboid& cuboid) {
  cuboid.vao = ctx.gen_vao();
  glBindVertexArray(ctx.vao(cuboid.vao));

  glGenBuffers(1, &cuboid.vbo);
  glGenBuffers(1, &cuboid.ibo);

  std::array<geometry::Vector<3>, 8> vertices;

  geometry::Rectangle back_face = cuboid.geometry.back_face();
  vertices[0]                   = back_face.botleft();
  vertices[1]                   = back_face.botright();
  vertices[2]                   = back_face.topleft();
  vertices[3]                   = back_face.topright();

  geometry::Rectangle front_face = cuboid.geometry.front_face();
  vertices[4]                    = front_face.botleft();
  vertices[5]                    = front_face.botright();
  vertices[6]                    = front_face.topleft();
  vertices[7]                    = front_face.topright();

  glBindBuffer(GL_ARRAY_BUFFER, cuboid.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

  std::array<std::array<unsigned int, 3>, 12> indices = {{
    // Left face
    {5, 0, 7},
    {2, 7, 0},
    // Right face
    {1, 4, 3},
    {6, 3, 4},
    // Bottom face
    {5, 4, 0},
    {1, 0, 4},
    // Top face
    {2, 3, 7},
    {6, 7, 3},
    // Back face
    {0, 1, 2},
    {3, 2, 1},
    // Front face
    {4, 5, 6},
    {7, 6, 5},
  }};
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cuboid.ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
}
