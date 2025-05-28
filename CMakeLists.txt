cmake_minimum_required(VERSION 3.31)
project(mario_isn C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MACOSX_BUNDLE TRUE)
set(MACOSX_BUNDLE_BUNDLE_NAME "MarioISN")
set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.aymnms.marioisn")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0")
set(MACOSX_BUNDLE_LONG_VERSION_STRING "1.0")
set(MACOSX_BUNDLE_BUNDLE_VERSION "1.0")
set(MACOSX_BUNDLE_ICON_FILE MyIcon.icns)

# headers
include_directories(
        /opt/homebrew/include
        include
)

# Exécutable (cible)
add_executable(mario_isn MACOSX_BUNDLE
        src/main.c
        src/display.c
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
)

add_custom_command(TARGET mario_isn POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_BUNDLE_CONTENT_DIR:mario_isn>/Resources
)
add_custom_command(TARGET mario_isn POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/img/MyIcon.icns
        $<TARGET_BUNDLE_CONTENT_DIR:mario_isn>/Resources/MyIcon.icns
)

set_source_files_properties(${CMAKE_SOURCE_DIR}/img/MyIcon.icns
        PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
)

# Bibliothèques
target_link_libraries(mario_isn
        /opt/homebrew/lib/libSDL2.dylib
        /opt/homebrew/lib/libSDL2_image.dylib
        /opt/homebrew/lib/libSDL2_mixer.dylib
)

# Ressources
set(ASSETS
        ${CMAKE_SOURCE_DIR}/bin
        ${CMAKE_SOURCE_DIR}/img
        ${CMAKE_SOURCE_DIR}/musique
)

foreach(asset IN LISTS ASSETS)
    get_filename_component(asset_name ${asset} NAME)
    add_custom_command(TARGET mario_isn POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${asset}
            $<TARGET_BUNDLE_CONTENT_DIR:mario_isn>/${asset_name}
    )
endforeach()