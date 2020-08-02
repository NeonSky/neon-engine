# NOTE: This recipe needs to be at the top to cover calling "make" without arguments
.PHONY: help
help:
	@ echo "Welcome to ECS Scenes!"
	@ echo ""
	@ echo "Options"
	@ echo "- build"
	@ echo "- coverage"
	@ echo "- dependencies"
	@ echo "- docker-hub-push"
	@ echo "- docker-linter-build"
	@ echo "- docker-linter-run"
	@ echo "- docs"
	@ echo "- format"
	@ echo "- format-check"
	@ echo "- linter"
	@ echo "- help"
	@ echo "- rebuild"
	@ echo "- retidy"
	@ echo "- run"
	@ echo "- run-tests"
	@ echo "- setup"
	@ echo "- tidy"
	@ echo "- tidy-check"

.PHONY: build
build:
	cd build && cmake .. && make

# Produces coverage report: ./build/CODE_COVERAGE/index.html
#
# Explanation:
# 1. Generates a baseline report through --intial (this makes sure that files with no test coverage are also included).
# 2. Generates a test report without --intial, and then merges it with the baseline.
# 3. Generates a HTML document from the final report, in order to better visualize the report.
.PHONY: coverage
coverage: build
	rm -rf build/CODE_COVERAGE
	lcov --directory build --zerocounters --rc lcov_branch_coverage=1
	lcov --initial --directory build --capture --output-file build/code_coverage_base.info --rc lcov_branch_coverage=1
	make run-tests
	lcov --directory build --capture --output-file build/code_coverage_test.info --rc lcov_branch_coverage=1
	lcov --add-tracefile build/code_coverage_base.info --add-tracefile build/code_coverage_test.info -o build/code_coverage.info  --rc lcov_branch_coverage=1
	lcov --remove build/code_coverage.info "/usr/*" "include*" "*test*" "*vendor*" -o build/code_coverage.info  --rc lcov_branch_coverage=1
	rm build/code_coverage_base.info build/code_coverage_test.info
	genhtml build/code_coverage.info --branch-coverage --output-directory build/CODE_COVERAGE --rc genhtml_branch_coverage=1

.PHONY: dependencies
dependencies:
	sudo vcpkg install glfw3 boost stb imgui[bindings] spdlog cpp-httplib nlohmann-json entt tinygltf gtest

# FIXME: Takes ages when including all the paths
# docker-slim build ecs-scenes --http-probe=false --tag=neonsky/ecs-scenes --include-path=/usr/share/cmake-3.17 --include-path=/usr/share/vcpkg/scripts/buildsystems/vcpkg.cmake --include-bin=/usr/sbin/make --include-bin=/usr/sbin/cmake --include-bin=/usr/bin/ls --include-shell
.PHONY: docker-hub-push
docker-hub-push:
	docker build -t ecs-scenes -f ci/Dockerfile .
	docker tag ecs-scenes neonsky/ecs-scenes
	docker push neonsky/ecs-scenes

.PHONY: docker-linter-build
docker-linter-build:
	docker build -t ecs-scenes-linter -f ci/linter.Dockerfile .

.PHONY: docker-linter-run
docker-linter-run:
	docker run ecs-scenes-linter

.PHONY: docs
docs:
	cd docs && make html
	$(eval WARNINGS = $(shell cat docs/doxygen/warnings.log | wc -l))
	@if (( $(WARNINGS) > 0)); then echo "There were warnings! See warnings.log"; fi

.PHONY: format
format:
	clang-format -i $(shell find src/ -name '*.[ch]pp' -not -path 'src/vendor/*') --Werror

.PHONY: format-check
format-check:
	$(eval PRE_HASH = $(shell ls -alR --full-time ./src | sha1sum))
	$(eval POST_HASH = $(shell clang-format -i $(shell find src/ -name '*.[ch]pp' -not -path 'src/vendor/*') --Werror && ls -alR --full-time ./src | sha1sum))
	@if [ "$(POST_HASH)" != "$(PRE_HASH)" ]; then exit 1; fi

.PHONY: linter
linter: format-check tidy-check run-tests

.PHONY: rebuild
rebuild:
	cd build && make rebuild_cache && cmake .. && make

.PHONY: retidy
retidy:
	$(eval CHANGED_FILES=$(shell git diff HEAD --name-only | grep -E "*.[ch]pp" | grep -Ev "*/(vendor|test)/*" || echo 0))
	@if [ $(CHANGED_FILES) != 0 ]; then \
		clang-tidy --fix -p build/compile_commands.json $(CHANGED_FILES); \
	fi

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
