#include "scene.hpp"

using namespace engine::scene;

IScene::IScene(SceneAPI& api) : _api(api) {}

IScene::~IScene() = default;
