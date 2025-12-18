FROM ubuntu:22.04

WORKDIR /app 

RUN --mount=type=cache,target=/var/cache/apt,id=apt-cache \
    --mount=type=cache,target=/var/lib/apt,id=apt-lib \
    apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    unzip \
    zip \
    python3 \
    pkg-config \
    ccache \
    ninja-build \ 
    tree

COPY vcpkg.json .

RUN git clone https://github.com/microsoft/vcpkg.git /vcpkg
RUN /vcpkg/bootstrap-vcpkg.sh -disableMetrics 

RUN --mount=type=cache,target=/vcpkg/downloads,id=vcpkg-downloads \
    --mount=type=cache,target=/vcpkg/buildtrees,id=vcpkg-buildtrees \
    --mount=type=cache,target=/vcpkg/packages,id=vcpkg-packages \
     /vcpkg/vcpkg install --triplet x64-linux

RUN mkdir -p app/build
RUN useradd -m dev
RUN chown -R dev:dev /vcpkg

USER dev

COPY . .

CMD ["bash"]