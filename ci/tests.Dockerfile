FROM neonsky/ecs-scenes:latest

USER aur

WORKDIR /home/aur/ecs-scenes/build
WORKDIR /home/aur/ecs-scenes
COPY res res
COPY src src
COPY CMakeLists.txt .
COPY Makefile .
RUN make build

CMD ["/home/aur/ecs-scenes/build/ECS_Scenes_Test"]
