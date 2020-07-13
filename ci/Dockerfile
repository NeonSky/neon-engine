FROM archlinux/base:latest

# Setup yay workspace.
RUN echo '[multilib]' >> /etc/pacman.conf && \
    echo 'Include = /etc/pacman.d/mirrorlist' >> /etc/pacman.conf && \
    pacman --noconfirm -Syyu && \
    pacman --noconfirm -S base-devel git && \
    useradd -m -r -s /bin/bash aur && \
    passwd -d aur && \
    echo 'aur ALL=(ALL) ALL' > /etc/sudoers.d/aur && \
    mkdir -p /home/aur && \
    chown -R aur:aur /home/aur && \
    mkdir /build && \
    chown -R aur:aur /build && \
    cd /build && \
    sudo -u aur git clone --depth 1 https://aur.archlinux.org/yay.git && \
    cd yay && \
    sudo -u aur makepkg --noconfirm -si && \
    sudo -u aur yay --afterclean --removemake --save && \
    pacman -Qtdq | xargs -r pacman --noconfirm -Rcns && \
    rm -rf /home/aur/.cache && \
    rm -rf /build

USER aur

RUN yay -S --noconfirm vcpkg-git unzip cmake xorg
RUN sudo vcpkg update
RUN sudo vcpkg install glfw3
RUN yay -S --noconfirm xf86-input-libinput mesa-demos
RUN sudo vcpkg install imgui[bindings]
RUN sudo vcpkg install glm
RUN sudo vcpkg install boost
RUN sudo vcpkg install stb
RUN sudo vcpkg install spdlog
RUN sudo vcpkg install cpp-httplib
RUN sudo vcpkg install nlohmann-json
RUN sudo vcpkg install entt
RUN sudo vcpkg install tinygltf
RUN sudo vcpkg install gtest
