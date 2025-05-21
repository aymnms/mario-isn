cmake_minimum_required(VERSION 3.31)
project(mario_isn C)

set(CMAKE_C_STANDARD 99)

# Ajoute les headers de SDL2 (macOS Homebrew)
include_directories(/opt/homebrew/include)

add_executable(mario_isn src/main.c)

# Lie les bibliothèques SDL2
target_link_libraries(mario_isn
        /opt/homebrew/lib/libSDL2.dylib
        /opt/homebrew/lib/libSDL2_mixer.dylib
)