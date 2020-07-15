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
	@ echo "- run-tests"
	@ echo "- setup"
	@ echo "- static-analysis"
	@ echo "- tidy"

.PHONY: build
build:
	cd build && cmake .. && make

.PHONY: dependencies
dependencies:
	sudo vcpkg install glfw3 glm boost stb imgui[bindings] spdlog cpp-httplib nlohmann-json entt tinygltf gtest

# FIXME: Takes ages when including all the paths
# docker-slim build ecs-scenes --http-probe=false --tag=neonsky/ecs-scenes --include-path=/usr/share/cmake-3.17 --include-path=/usr/share/vcpkg/scripts/buildsystems/vcpkg.cmake --include-bin=/usr/sbin/make --include-bin=/usr/sbin/cmake --include-bin=/usr/bin/ls --include-shell
.PHONY: docker-hub-push
docker-hub-push:
	docker build -t ecs-scenes -f ci/Dockerfile .
	docker tag ecs-scenes neonsky/ecs-scenes
	docker push neonsky/ecs-scenes

.PHONY: docker-tests-build
docker-linter-build:
	docker build -t ecs-scenes-linter -f ci/linter.Dockerfile .

.PHONY: docker-tests-run
docker-linter-run:
	docker run ecs-scenes-linter

.PHONY: format
format:
	clang-format -i $(shell find src/ -name '*.[ch]pp' -not -path 'src/vendor/*')

.PHONY: linter
linter: tidy-check run-tests

.PHONY: run
run:
	./build/ECS_Scenes

.PHONY: run-tests
run-tests:
	./build/ECS_Scenes_Test

.PHONY: setup
setup: dependencies build run

.PHONY: tidy
tidy:
	$(eval FILES=$(shell find src -name '*.[ch]pp' -not -path '*/vendor/*' -and -not -path '*/test/*'))
	clang-tidy --fix -p build/compile_commands.json $(FILES)

.PHONY: tidy-check
tidy-check:
	$(eval FILES=$(shell find src -name '*.[ch]pp' -not -path '*/vendor/*' -and -not -path '*/test/*'))
	clang-tidy -p build/compile_commands.json $(FILES)
