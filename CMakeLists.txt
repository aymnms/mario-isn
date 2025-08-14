cmake_minimum_required(VERSION 3.20)
project(mario_isn C)

# Langage & bundle macOS
set(CMAKE_C_STANDARD 99)
set(CMAKE_MACOSX_BUNDLE TRUE)
set(MACOSX_BUNDLE_BUNDLE_NAME "MarioISN")
set(MACOSX_BUNDLE_GUI_IDENTIFIER "fr.aymnms.marioisn")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0")
set(MACOSX_BUNDLE_LONG_VERSION_STRING "1.0")
set(MACOSX_BUNDLE_BUNDLE_VERSION "1.0")
set(MACOSX_BUNDLE_ICON_FILE MyIcon.icns)

# Pour VS Code / IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Trouver SDL2 via les packages CMake fournis par Homebrew
find_package(SDL2       REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)

# Exécutable (cible)
add_executable(mario_isn MACOSX_BUNDLE
        src/main.c
        src/display.c
        src/path.c
        src/menu/init_menu.c
        src/menu/menu.c
        src/game/init_game.c
        src/game/GAME.c
        src/game/conditions.c
        src/game/mechant/addElem.c
        src/game/mechant/bowser.c
        src/game/mechant/contact_mechant.c
        src/game/mechant/deplacement_mechant.c
        src/game/mechant/refresh_mechant.c
        src/game/joueur/animation.c
        src/game/joueur/deplacement_joueur.c
        src/game/joueur/music.c
        src/game/joueur/niveau.c
        src/game/joueur/saut_joueur.c
        ${CMAKE_SOURCE_DIR}/ressources/MyIcon.icns
)

# Indique où la placer dans le bundle
set_source_files_properties(${CMAKE_SOURCE_DIR}/ressources/MyIcon.icns
    PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# Portée des includes du projet (headers locaux)
target_include_directories(mario_isn PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Lien contre SDL2 (targets importées = include + libs + defines gérés)
target_link_libraries(mario_isn PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
)

# Copie des assets dans le bundle .app (Resources)
add_custom_command(TARGET mario_isn POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_BUNDLE_CONTENT_DIR:mario_isn>/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/ressources
            $<TARGET_BUNDLE_CONTENT_DIR:mario_isn>/Resources
)
