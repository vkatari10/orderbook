add_executable(perf_tests
    shared/dynamic_ringbuffer_perf.cpp
)

target_include_directories(perf_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(benchmark REQUIRED)
target_link_libraries(perf_tests benchmark::benchmark)

