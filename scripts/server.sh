#! /usr/bin/bash
cmake -S /app -B /app/build -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake \
  && cmake --build /app/build --target server_app \
  && ./build/apps/server/server_app
