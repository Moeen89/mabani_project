cmake_minimum_required(VERSION 3.21)
project(u C)

set(CMAKE_C_STANDARD 99)

add_executable(u main.c TextureLoader.c TextureLoader.h other_functions.c other_functions.h file_functions.c file_functions.h game.c game.h map_generator.c map_generator.h)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
target_link_libraries(u m)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::Mixer SDL2::TTF)