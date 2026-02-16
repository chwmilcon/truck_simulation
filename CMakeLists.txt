cmake_minimum_required(VERSION 3.15)
project(LunarMiningSimulation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

# Optimization flags for Release build
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Source files
set(SOURCES
    lib/truck_simulation.cpp
    src/main.cpp
)

set(HEADERS
    hdr/truck_simulation.hpp
)
include_directories(
    hdr
)
# Create library from simulation code
add_library(truck_simulation_lib STATIC lib/truck_simulation.cpp hdr/truck_simulation.hpp)

add_executable(truck_simulation src/main.cpp)
target_link_libraries(truck_simulation truck_simulation_lib)

# Installation
install(TARGETS truck_simulation DESTINATION bin)

# Print build information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Test executable
add_executable(simulation_test tests/simulation_test.cpp)
target_include_directories(simulation_test PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(simulation_test 
    truck_simulation_lib 
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(simulation_test)

add_executable(test_event tests/test_event.cpp)
target_include_directories(test_event PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_event 
    truck_simulation_lib 
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_event)

add_executable(test_mining_truck tests/test_mining_truck.cpp)
target_include_directories(test_mining_truck PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_mining_truck 
    truck_simulation_lib 
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_mining_truck)

add_executable(test_unload_station tests/test_unload_station.cpp)
target_include_directories(test_unload_station PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_unload_station 
    truck_simulation_lib 
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_unload_station)

add_executable(test_truck_stats tests/test_truck_stats.cpp)
target_include_directories(test_truck_stats PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_truck_stats 
    truck_simulation_lib 
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_truck_stats)

add_executable(test_station_stats tests/test_station_stats.cpp)
target_include_directories(test_station_stats PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_station_stats 
    truck_simulation_lib 
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_station_stats)
