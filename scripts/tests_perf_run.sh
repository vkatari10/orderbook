#! /usr/bin/bash
cmake -S /app -B /app/build -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DBUILD_PERF_TESTING=ON \
  -DBUILD_UNIT_TESTING=OFF \
  && cmake --build /app/build --target perf_tests \
  && ./build/tests/perf/perf_tests