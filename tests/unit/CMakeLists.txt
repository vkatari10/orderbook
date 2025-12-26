add_executable(unit_tests
    shared/dynamic_ringbuffer_test.cpp
    shared/ringbuffer_test.cpp
    orderbook/orderbook_test.cpp

    matching-engine/limit_order_test.cpp
)

target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(GTest REQUIRED)

target_link_libraries(unit_tests PRIVATE 
    GTest::gtest_main 
    orderbook
    matching_engine
)

include(GoogleTest)
gtest_discover_tests(unit_tests)