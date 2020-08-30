FROM neonsky/neon-engine:latest

USER aur

RUN yay -Syu --noconfirm
RUN yay -S --noconfirm clang
WORKDIR /home/aur/neon-engine/build
WORKDIR /home/aur/neon-engine
COPY res res
COPY src src
COPY CMakeLists.txt .
COPY .clang-format .
COPY .clang-tidy .
COPY Makefile .
RUN make build

CMD ["make", "linter"]
