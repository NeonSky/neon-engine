# NOTE: This recipe needs to be at the top to cover calling "make" without arguments
.PHONY: help
help:
	@ echo "Welcome to ECS Scenes!"
	@ echo ""
	@ echo "Options"
	@ echo "- build"
	@ echo "- dependencies"
	@ echo "- docker-hub-push"
	@ echo "- docker-tests-build"
	@ echo "- docker-tests-run"
	@ echo "- format"
	@ echo "- help"
	@ echo "- run"
	@ echo "- setup"
	@ echo "- tidy"

.PHONY: build
build:
	cd build && cmake .. && make

.PHONY: dependencies
dependencies:
	sudo vcpkg install glfw3 glm boost stb imgui[bindings] spdlog cpp-httplib nlohmann-json entt tinygltf gtest

.PHONY: docker-hub-push
docker-hub-push:
	docker build -t ecs-scenes -f ci/Dockerfile .
	# FIXME: Takes ages when including all the paths
	# docker-slim build ecs-scenes --http-probe=false --tag=neonsky/ecs-scenes --include-path=/usr/share/cmake-3.17 --include-path=/usr/share/vcpkg/scripts/buildsystems/vcpkg.cmake --include-bin=/usr/sbin/make --include-bin=/usr/sbin/cmake --include-bin=/usr/bin/ls --include-shell
	docker tag ecs-scenes neonsky/ecs-scenes
	docker push neonsky/ecs-scenes

.PHONY: docker-tests-build
docker-tests-build:
	docker build -t ecs-scenes-tests -f ci/tests.Dockerfile .

.PHONY: docker-tests-run
docker-tests-run:
	docker run ecs-scenes-tests /home/aur/ecs-scenes/build/ECS_Scenes_Test

.PHONY: format
format:
	clang-format -i $(find src/ -name '*.[ch]pp' -not -path 'src/vendor/*')

.PHONY: run
run:
	cd build && ./build/ECS_Scenes

.PHONY: setup
setup: dependencies build run

# cppcoreguidelines-*, clang-analyzer-*, boost-*, bugprone-*, performance-*, readability-*
.PHONY: tidy
tidy:
	clang-tidy --checks="modernize-*" -p build/compile_commands.json $(find src -name '*.[ch]pp' -not -path '*/vendor/*' -and -not -path '*/test/*') -- -std=c++17


# maybe just *.cpp?
# --fix
# --header-filter
# --fix-errors
