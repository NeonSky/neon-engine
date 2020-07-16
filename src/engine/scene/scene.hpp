#pragma once

namespace engine::scene {

  class IScene {
  public:
    virtual void update() {}
    virtual void render() {}
    virtual void gui() {}

  protected:
    ~IScene()             = default;
    IScene(IScene const&) = default;
    auto operator=(IScene const&) -> IScene& = default;
    IScene(IScene&&)                         = default;
    auto operator=(IScene &&) -> IScene& = default;
  };
}
