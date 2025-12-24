add_executable(server_app server.cpp)

target_link_libraries(server_app PRIVATE 
    orderbook 
    matching_engine
)

