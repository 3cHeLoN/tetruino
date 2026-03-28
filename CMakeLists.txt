cmake_minimum_required(VERSION 3.16)
project(tetruino VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${SDL2_LIBRARY_DIRS} ${SDL2_MIXER_LIBRARY_DIRS})
add_definitions(${SDL2_CFLAGS_OTHER})

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(tetruino ${SOURCES})

target_include_directories(tetruino PRIVATE ${SDL2_INCLUDE_DIRS})

target_compile_options(tetruino PRIVATE -Wall -Wextra -O3)

target_link_libraries(tetruino ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

# install target
install(TARGETS tetruino RUNTIME DESTINATION bin)
