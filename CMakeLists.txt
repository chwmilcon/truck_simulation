# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Generate compile_commands.json")
set(GFLAGS_USE_TARGET_NAMESPACE ON CACHE BOOL "Use target namespace for gflags")

# Set the project name
project(truck_simulation)

# Set the C++ standard to 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(
    hdr
    /usr/local/include
    /opt/homebrew/include
)

# Find glog and gflags libraries
find_package(glog REQUIRED)
find_package(gflags REQUIRED)

# Add a library target
add_library(truck_simulation_lib STATIC
    lib/truck_simulation.cpp
)

# Add compile options and definitions to the library
target_compile_options(truck_simulation_lib PRIVATE
    -O0 -g
    -DGFLAGS_USE_TARGET_NAMESPACE=true
)
target_compile_definitions(truck_simulation_lib PRIVATE DEBUG)

# Link glog and gflags libraries to truck_simulation_lib
target_link_libraries(truck_simulation_lib
    glog::glog
    gflags::gflags
)

# Add an executable target
add_executable(truck_simulation
    src/main.cpp
)

# Add compile options and definitions to the executable
target_compile_options(truck_simulation PRIVATE
    -O0 -g
)
target_compile_definitions(truck_simulation PRIVATE DEBUG)

# Link the library to the executable
target_link_libraries(truck_simulation
    truck_simulation_lib
    glog::glog
    gflags::gflags
)
