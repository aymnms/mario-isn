
cmake_minimum_required(VERSION 3.20)
project(mario_isn C)

# =====================================
# Language / IDE helpers
# =====================================
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Previously nothing here at all, so 199 real warnings (missing function
# prototypes, implicit conversions, variable shadowing...) had silently
# accumulated across the codebase -- see AUDIT.md §9 / PLAN.md J5-3. All of
# them are now fixed, and -Werror turns any future regression of this kind
# into a build failure instead of something that silently piles back up.
#
# MSVC's /W4 is intentionally NOT paired with /WX here: its warning set is
# different from Clang/GCC's and has never been audited/fixed the same way
# (no local Windows toolchain available to verify against, only CI) -- /W4
# alone still surfaces them for a human to read, without risking turning an
# unverified, possibly-noisy warning into a hard Windows CI failure.
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -Werror)
elseif(MSVC)
  add_compile_options(/W4)
endif()

# =====================================
# Platform-specific bundle/target settings
# =====================================
# On macOS we build an .app bundle; on other OSes we build a regular executable
if(APPLE)
  set(PLATFORM_BUNDLE MACOSX_BUNDLE)
  set(CMAKE_MACOSX_BUNDLE TRUE)
  set(MACOSX_BUNDLE_BUNDLE_NAME "MarioISN")
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "fr.aymnms.marioisn")
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING "1.3.8")
  set(MACOSX_BUNDLE_LONG_VERSION_STRING  "1.0")
  set(MACOSX_BUNDLE_BUNDLE_VERSION       "1.3.8")
  set(MACOSX_BUNDLE_ICON_FILE MyIcon.icns)
elseif(WIN32)
  # GUI subsystem: without this, Windows opens a console window alongside
  # the game (SDL2::SDL2main still provides the real entry point either way).
  set(PLATFORM_BUNDLE WIN32)

  # Both mario_isn.exe and vcpkg's prebuilt SDL2.dll are linked against the
  # MSVC runtime (VCRUNTIME140.dll, msvcp140.dll, the api-ms-win-crt-*.dll
  # Universal CRT forwarders) -- none of which ship with a bare Windows
  # install and none of which were being bundled, so the game failed to
  # launch on any machine without the Visual C++ Redistributable already
  # installed. InstallRequiredSystemLibraries is CMake's standard mechanism
  # for locating the exact redistributable files matching the detected
  # compiler; copied next to the .exe in the WIN32 packaging block below.
  set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
  include(InstallRequiredSystemLibraries)
endif()

# =====================================
# Dependencies: SDL2 family
# Try CMake config packages first (Homebrew/vcpkg), fallback to pkg-config (Linux)
# =====================================
find_package(SDL2       QUIET CONFIG)
find_package(SDL2_image QUIET CONFIG)
find_package(SDL2_mixer QUIET CONFIG)

if(APPLE)
  # Homebrew's "sdl2" is now sdl2-compat: an SDL2-ABI shim that dlopen()s the
  # real libSDL3.dylib at runtime instead of linking it -- invisible to
  # fixup_bundle's otool-based dependency walk. Located here (rather than
  # inline in FixupBundleMacOS.cmake) so SDL3_DIR can be hinted the same way
  # as SDL2_DIR/etc. for the cross-compiled Intel build. See the
  # fixup_bundle POST_BUILD step below for where this gets bundled.
  find_package(SDL3 QUIET CONFIG)
endif()

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
set(DOMAIN_SOURCES
        src/domain/physics.c
        src/domain/grid.c
        src/domain/collision.c
        src/domain/movement.c
        src/domain/tile.c
)

# Sets mario_isn.exe's icon (Explorer/taskbar/Alt+Tab) -- otherwise it uses
# a generic default icon, one more thing that makes an unsigned executable
# look untrustworthy.
if(WIN32)
  set(WIN32_RESOURCES ${CMAKE_SOURCE_DIR}/packaging/windows/mario_isn.rc)
endif()

add_executable(mario_isn ${PLATFORM_BUNDLE}
        ${DOMAIN_SOURCES}
        ${WIN32_RESOURCES}
        src/globals.c
        src/main.c
        src/display.c
        src/path.c
        src/menu/init_menu.c
        src/menu/MENU.c
        src/game/init_game.c
        src/game/GAME.c
        src/game/conditions.c
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
  # On Windows, SDL.h #defines main to SDL_main; SDL2::SDL2main provides the
  # real entry point that calls back into it. $<TARGET_NAME_IF_EXISTS:...>
  # is a no-op on macOS/Linux where that target doesn't exist.
  target_link_libraries(mario_isn PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
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
# Unit tests (SDL-free domain logic only -- see src/domain/)
# =====================================
add_executable(domain_tests
        ${DOMAIN_SOURCES}
        tests/domain_tests.c
)
target_include_directories(domain_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(NOT HAVE_SDL_PKGCFG)
  target_link_libraries(domain_tests PRIVATE SDL2::SDL2)
else()
  target_include_directories(domain_tests PRIVATE ${SDL2_INCLUDE_DIRS})
  target_link_libraries(domain_tests PRIVATE ${SDL2_LINK_LIBRARIES})
endif()

enable_testing()
add_test(NAME domain_tests COMMAND domain_tests)

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

  # Bundle SDL2/SDL2_image/SDL2_mixer (and their transitive dylibs) into the
  # .app so it runs without Homebrew SDL2 installed on the target machine.
  # Release-only: re-fixing ~100 dylibs on every relink is too slow for the
  # Debug dev loop (make run), and local dev already has Homebrew SDL2.
  set(FIXUP_BUNDLE_EXTRA_ARGS "")
  if(TARGET SDL3::SDL3)
    list(APPEND FIXUP_BUNDLE_EXTRA_ARGS -DSDL3_LIBRARY=$<TARGET_FILE:SDL3::SDL3>)
  endif()

  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET mario_isn POST_BUILD
        COMMAND ${CMAKE_COMMAND}
                -DBUNDLE_PATH=$<TARGET_BUNDLE_DIR:mario_isn>
                ${FIXUP_BUNDLE_EXTRA_ARGS}
                -P ${CMAKE_SOURCE_DIR}/cmake/FixupBundleMacOS.cmake
    )
  endif()

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

  # Bundle the Visual C++ Redistributable DLLs -- see the InstallRequiredSystemLibraries
  # call above for why. VCPKG_APPLOCAL_DEPS already copies SDL2/SDL2_image/SDL2_mixer's
  # own DLLs; this covers the MSVC runtime none of them ship with.
  if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
    add_custom_command(TARGET mario_isn POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
                $<TARGET_FILE_DIR:mario_isn>
    )
  endif()

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

  # Bundle SDL2/SDL2_image/SDL2_mixer (and their transitive .so deps) next to
  # the executable so it runs without those libs installed system-wide.
  # Release-only, same rationale as the macOS fixup_bundle step above.
  # No-op with a warning if `patchelf` isn't available (e.g. plain dev build).
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET mario_isn POST_BUILD
        COMMAND ${CMAKE_SOURCE_DIR}/scripts/bundle_libs_linux.sh
                $<TARGET_FILE:mario_isn>
                $<TARGET_FILE_DIR:mario_isn>/lib
    )
  endif()
endif()
