#include "rectangle_renderer.hpp"

#include "../component/global_transform.hpp"
#include "../component/render_info.hpp"

using namespace engine::graphics::system;

RectangleRenderer::RectangleRenderer()
        : _shader(Shader("unicolor.vert", "color.frag")) {}

void RectangleRenderer::update(architecture::ECS& ecs) {
  auto& render_info = ecs.get<component::RenderInfo>(ecs.view<component::RenderInfo>()[0]);
  auto& ctx         = render_info.context.get();

  _shader.use();

  for (auto entity : ecs.view<component::Rectangle>()) {
    auto& rectangle = ecs.get<component::Rectangle>(entity);

    if (rectangle.vao == 0)
      compile_rectangle(ctx, rectangle);

    glBindVertexArray(ctx.vao(rectangle.vao));

    glBindBuffer(GL_ARRAY_BUFFER, rectangle.vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0U, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle.ibo);

    auto mvp = render_info.view_projection * ecs.get<component::GlobalTransform>(entity).matrix;
    _shader.set_uniform_mat4("model_view_projection", mvp);
    _shader.set_uniform_rgb("color", rectangle.color);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  }

  glBindVertexArray(0);
}

void RectangleRenderer::compile_rectangle(api::IContext& ctx, component::Rectangle& rectangle) {
  rectangle.vao = ctx.gen_vao();
  glBindVertexArray(ctx.vao(rectangle.vao));

  glGenBuffers(1, &rectangle.vbo);
  glGenBuffers(1, &rectangle.ibo);

  std::array<geometry::Vector<3>, 4> vertices = {
    rectangle.geometry.botleft(),
    rectangle.geometry.botright(),
    rectangle.geometry.topleft(),
    rectangle.geometry.topright(),
  };

  glBindBuffer(GL_ARRAY_BUFFER, rectangle.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

  const std::array<unsigned int, 6> indices = {
    0,
    1,
    2,

    3,
    2,
    1,
  };

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle.ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
}
