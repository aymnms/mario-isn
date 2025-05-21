cmake_minimum_required(VERSION 3.31)
project(mario_isn C)

set(CMAKE_C_STANDARD 99)

# headers
include_directories(
        /opt/homebrew/include
        include
)

add_executable(mario_isn
        src/main.c
        src/display.c
        src/menu/init_menu.c
        src/game/joueur/music.c
        src/menu/menu.c
)

# libraries
target_link_libraries(mario_isn
        /opt/homebrew/lib/libSDL2.dylib
        /opt/homebrew/lib/libSDL2_image.dylib
        /opt/homebrew/lib/libSDL2_mixer.dylib
)