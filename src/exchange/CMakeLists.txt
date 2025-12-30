add_library(exchange STATIC exchange.cpp)

target_include_directories(exchange PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(concurrentqueue CONFIG REQUIRED)
find_package(quickfix CONFIG REQUIRED)
target_link_libraries(exchange PUBLIC concurrentqueue::concurrentqueue quickfix)

