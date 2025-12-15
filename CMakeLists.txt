cmake_minimum_required(
    VERSION 3.15...4.1
) # required line to define CMake version we want to use 

project( # also required line after setting the version
    OrderBook 
    VERSION 1.0
    DESCRIPTION "Orderbook Data Structure"
    LANGUAGES CXX 
)

set(CMAKE_CXX_STANDARD 20) # equivalent to -std=c++20

add_executable(main main.cpp src/orderbook.cpp) 