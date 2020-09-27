#include "script.hpp"

using namespace engine::scene;

IScript::IScript() = default;

IScript::IScript([[maybe_unused]] SceneAPI& api,
                 [[maybe_unused]] Node& root) {}
