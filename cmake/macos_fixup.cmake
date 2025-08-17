# cmake/fixup_bundle.cmake
cmake_minimum_required(VERSION 3.20)
include(BundleUtilities)

if(NOT DEFINED APP)
  message(FATAL_ERROR "fixup_bundle: APP variable not set")
endif()

set(app "${APP}")
set(frameworks_dir "${app}/Contents/Frameworks")
file(MAKE_DIRECTORY "${frameworks_dir}")

# Récupère des dossiers passés par la commande appelante
set(search_dirs "")
if(DEFINED SEARCH_DIRS)
  # split ';' list to CMake list
  string(REPLACE ";" ";" search_dirs "${SEARCH_DIRS}")
endif()

# Essaie aussi de déduire le prefix Homebrew, si disponible
# (utile pour libwebp, libjxl, libpng, libjpeg, libtiff, etc.)
if(NOT DEFINED BREW_PREFIX)
  execute_process(COMMAND brew --prefix
                  OUTPUT_VARIABLE BREW_PREFIX
                  OUTPUT_STRIP_TRAILING_WHITESPACE
                  ERROR_QUIET)
endif()

if(EXISTS "${BREW_PREFIX}")
  list(APPEND search_dirs
    "${BREW_PREFIX}/lib"
    "${BREW_PREFIX}/opt"
    "${BREW_PREFIX}/opt/webp/lib"
    "${BREW_PREFIX}/opt/libjxl/lib"
    "${BREW_PREFIX}/opt/libpng/lib"
    "${BREW_PREFIX}/opt/jpeg/lib"
    "${BREW_PREFIX}/opt/jpeg-turbo/lib"
    "${BREW_PREFIX}/opt/libtiff/lib"
    "${BREW_PREFIX}/opt/ogg/lib"
    "${BREW_PREFIX}/opt/vorbis/lib"
    "${BREW_PREFIX}/opt/opus/lib"
    "${BREW_PREFIX}/opt/flac/lib"
  )
endif()

# Débogage (facultatif) :
message(STATUS "fixup_bundle")
message(STATUS "  app='${app}/Contents/MacOS/mario_isn'")
message(STATUS "  dirs='${search_dirs}'")

# Copie les dylibs et réécrit leurs install_name
fixup_bundle("${app}/Contents/MacOS/mario_isn" "" "${search_dirs}")