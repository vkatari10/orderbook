add_executable(server_app server.cpp)

find_package(quickfix CONFIG REQUIRED)

target_link_libraries(server_app PRIVATE 
    orderbook 
    matching_engine
    quickfix
    gateway
    exchange
)