cmake_minimum_required(VERSION 3.20)
project(herl VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(dpp CONFIG REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Main executable
add_executable(herl 
    src/main.cpp
)

target_link_libraries(herl PRIVATE dpp::dpp)

# Compiler options
if(MSVC)
  target_compile_options(herl PRIVATE /W4 /permissive-)
else()
  target_compile_options(herl PRIVATE -Wall -Wextra -Wpedantic)
endif()
