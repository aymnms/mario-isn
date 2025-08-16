
cmake_minimum_required(VERSION 3.20)
project(mario_isn C)

# =====================================
# Language / IDE helpers
# =====================================
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# =====================================
# Platform-specific bundle/target settings
# =====================================
# On macOS we build an .app bundle; on other OSes we build a regular executable
if(APPLE)
  set(PLATFORM_BUNDLE MACOSX_BUNDLE)
  set(CMAKE_MACOSX_BUNDLE TRUE)
  set(MACOSX_BUNDLE_BUNDLE_NAME "MarioISN")
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "fr.aymnms.marioisn")
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0.0")
  set(MACOSX_BUNDLE_LONG_VERSION_STRING  "1.0")
  set(MACOSX_BUNDLE_BUNDLE_VERSION       "1.0.0")
  set(MACOSX_BUNDLE_ICON_FILE MyIcon.icns)
endif()

# =====================================
# Dependencies: SDL2 family
# Try CMake config packages first (Homebrew/vcpkg), fallback to pkg-config (Linux)
# =====================================
find_package(SDL2       QUIET CONFIG)
find_package(SDL2_image QUIET CONFIG)
find_package(SDL2_mixer QUIET CONFIG)

if(NOT SDL2_FOUND OR NOT SDL2_image_FOUND OR NOT SDL2_mixer_FOUND)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(SDL2        REQUIRED sdl2)
  pkg_check_modules(SDL2_image  REQUIRED SDL2_image)
  pkg_check_modules(SDL2_mixer  REQUIRED SDL2_mixer)
  set(HAVE_SDL_PKGCFG TRUE)
endif()

# =====================================
# Executable target
# =====================================
add_executable(mario_isn ${PLATFORM_BUNDLE}
        src/main.c
        src/display.c
        src/path.c
        src/menu/init_menu.c
        src/menu/MENU.c
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

# Autorise les définitions communes (rétro-compatibilité GCC <10)
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(mario_isn PRIVATE -fcommon)
endif()

# Add headers include path (project-local)
target_include_directories(mario_isn PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link SDL depending on how it was found
if(NOT HAVE_SDL_PKGCFG)
  target_link_libraries(mario_isn PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer)
else()
  target_include_directories(mario_isn PRIVATE
    ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS})
  target_link_libraries(mario_isn PRIVATE
    ${SDL2_LINK_LIBRARIES} ${SDL2_image_LINK_LIBRARIES} ${SDL2_mixer_LINK_LIBRARIES})
endif()

# =====================================
# Resources / Assets
# =====================================
# Project resources layout at source:
#   ressources/
#     MyIcon.icns
#     img/  musique/  bin/

if(APPLE)
  # Add icon into the bundle and place it under Contents/Resources
  target_sources(mario_isn PRIVATE ${CMAKE_SOURCE_DIR}/ressources/MyIcon.icns)
  set_source_files_properties(${CMAKE_SOURCE_DIR}/ressources/MyIcon.icns
      PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

  # Copy assets into the app bundle Resources so SDL_GetBasePath() finds img/, musique/, bin/
  add_custom_command(TARGET mario_isn POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E make_directory
              $<TARGET_BUNDLE_CONTENT_DIR:mario_isn>/Resources
      COMMAND ${CMAKE_COMMAND} -E copy_directory
              ${CMAKE_SOURCE_DIR}/ressources/img
              $<TARGET_BUNDLE_CONTENT_DIR:mario_isn>/Resources/img
      COMMAND ${CMAKE_COMMAND} -E copy_directory
              ${CMAKE_SOURCE_DIR}/ressources/musique
              $<TARGET_BUNDLE_CONTENT_DIR:mario_isn>/Resources/musique
      COMMAND ${CMAKE_COMMAND} -E copy_directory
              ${CMAKE_SOURCE_DIR}/ressources/bin
              $<TARGET_BUNDLE_CONTENT_DIR:mario_isn>/Resources/bin
  )

elseif(WIN32)
  # On Windows, copy assets next to the .exe
  add_custom_command(TARGET mario_isn POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
              ${CMAKE_SOURCE_DIR}/ressources/img
              $<TARGET_FILE_DIR:mario_isn>/img
      COMMAND ${CMAKE_COMMAND} -E copy_directory
              ${CMAKE_SOURCE_DIR}/ressources/musique
              $<TARGET_FILE_DIR:mario_isn>/musique
      COMMAND ${CMAKE_COMMAND} -E copy_directory
              ${CMAKE_SOURCE_DIR}/ressources/bin
              $<TARGET_FILE_DIR:mario_isn>/bin
  )

elseif(UNIX)
  # On Linux, copy assets next to the executable
  add_custom_command(TARGET mario_isn POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
              ${CMAKE_SOURCE_DIR}/ressources/img
              $<TARGET_FILE_DIR:mario_isn>/img
      COMMAND ${CMAKE_COMMAND} -E copy_directory
              ${CMAKE_SOURCE_DIR}/ressources/musique
              $<TARGET_FILE_DIR:mario_isn>/musique
      COMMAND ${CMAKE_COMMAND} -E copy_directory
              ${CMAKE_SOURCE_DIR}/ressources/bin
              $<TARGET_FILE_DIR:mario_isn>/bin
  )
endif()
