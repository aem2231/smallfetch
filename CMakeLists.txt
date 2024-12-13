# Minimum CMake version required
cmake_minimum_required(VERSION 3.28)

# Project name and version
project(smallfetch VERSION 1.0 LANGUAGES C)

# Specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the executable with all source files
add_executable(smallfetch
        src/main.c
        src/cpu.c
        #src/hostname.c
        #src/kernel.c
        #src/packages.c
        #src/ram.c
        #src/ram_usage.c
)

# Add the include directory for header files
target_include_directories(smallfetch PRIVATE include/)
