cmake_minimum_required(VERSION 3.10)
project(CWars)

# Use clang++ and set flags
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find SDL2_ttf
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

# Find all .cpp source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable target
add_executable(CWars ${SOURCES})

# Include headers
target_include_directories(CWars PRIVATE include)

target_link_libraries(CWars 
    ${SDL2_LIBRARIES}
    SDL2_ttf
)
