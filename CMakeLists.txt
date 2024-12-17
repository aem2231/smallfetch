# Minimum CMake version required
cmake_minimum_required(VERSION 3.28)

# Enable warnings
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# Project name and version
project(smallfetch VERSION 1.0 LANGUAGES C)

# Specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the executable with all source files
add_executable(smallfetch
        src/main.c
        src/cpu.c
        src/hostname.c
        src/kernel.c
        src/memory.c
        src/packages.c
)

# Add the include directory for header files
target_include_directories(smallfetch PRIVATE include/)

# Link libraries
target_link_libraries(smallfetch m ncurses)

# Set the include path for ncurses
# set(CURSES_INCLUDE_PATH "/nix/store/inpspwqhgpld2zdk89hra7xjh3nxll2x-ncurses-6.4.20221231-dev/include")

# Set the library path for ncurses
# et(CURSES_LIBRARY "/nix/store/inpspwqhgpld2zdk89hra7xjh3nxll2x-ncurses-6.4.20221231-dev/lib/libncurses.so")

# Find the ncurses package
find_package(Curses REQUIRED)

# Include the ncurses directory and link the library
if(CURSES_FOUND)
    include_directories(${CURSES_INCLUDE_DIRS})
    target_link_libraries(smallfetch m ${CURSES_LIBRARIES})
else()
    message(FATAL_ERROR "NCurses not found")
endif()

# Add optimization flags for release builds
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native -funroll-loops -flto -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -funroll-loops -flto -DNDEBUG")
endif()

# Install rules
install(TARGETS smallfetch DESTINATION bin)


