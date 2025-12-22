cmake_minimum_required(
    VERSION 3.15...4.1
) # required line to define CMake version we want to use 

project( # also required line after setting the version
    OrderBook 
    VERSION 1.0
    DESCRIPTION "Orderbook Data Structure"
    LANGUAGES CXX 
)

# Visual Studio profiling settings
if (MSVC)
  add_compile_options(/Zi)
  add_link_options(/DEBUG /OPT:NOREF /OPT:NOICF /PROFILE)
endif()

set(CMAKE_CXX_STANDARD 20) # equivalent to -std=c++20
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0") # switch to just -O2 later

add_subdirectory(src/orderbook)
add_subdirectory(apps/server)