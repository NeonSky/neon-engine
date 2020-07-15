FROM neonsky/ecs-scenes:latest

USER aur

RUN yay -S --noconfirm clang
WORKDIR /home/aur/ecs-scenes/build
WORKDIR /home/aur/ecs-scenes
COPY res res
COPY src src
COPY CMakeLists.txt .
COPY .clang-format .
COPY .clang-tidy .
COPY Makefile .
RUN make build

CMD ["make", "linter"]
