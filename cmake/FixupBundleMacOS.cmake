# Copies SDL2/SDL2_image/SDL2_mixer (and their transitive dylibs) into the
# .app bundle and rewrites install names, so the app runs on a Mac without
# Homebrew SDL2 installed. Invoked as a POST_BUILD step (see CMakeLists.txt).
#
# Usage: cmake -DBUNDLE_PATH=<path-to-.app> -P FixupBundleMacOS.cmake
if(NOT DEFINED BUNDLE_PATH)
  message(FATAL_ERROR "BUNDLE_PATH must be set")
endif()

include(BundleUtilities)
fixup_bundle("${BUNDLE_PATH}" "" "")

# sdl2-compat (the modern Homebrew "sdl2" package) is an SDL2-ABI shim that
# dlopen()s the real libSDL3.dylib at runtime instead of linking it, so
# fixup_bundle's otool-based dependency walk above never sees it and never
# bundles it. Without this, the app fails at startup on a machine without
# Homebrew's SDL3 installed: "Fatal error! Cannot continue! Failed loading
# SDL3 library." sdl2-compat looks for it at exactly @loader_path/libSDL3.dylib
# relative to itself, so a plain copy into the same Frameworks directory
# (named libSDL3.dylib, following the symlink to get the real file) is
# sufficient -- no install_name rewriting needed, and libSDL3 itself only
# depends on system frameworks, nothing further to bundle.
if(SDL3_LIBRARY)
  if(EXISTS "${SDL3_LIBRARY}")
    message(STATUS "Bundling libSDL3 (sdl2-compat runtime dependency): ${SDL3_LIBRARY}")
    file(COPY "${SDL3_LIBRARY}"
         DESTINATION "${BUNDLE_PATH}/Contents/Frameworks"
         FOLLOW_SYMLINK_CHAIN)
    # FOLLOW_SYMLINK_CHAIN keeps the source's own filename, which may be the
    # versioned real file (e.g. libSDL3.0.dylib) rather than the unversioned
    # libSDL3.dylib name sdl2-compat's dlopen() actually looks for -- rename
    # to the exact expected name if they differ.
    get_filename_component(SDL3_COPIED_NAME "${SDL3_LIBRARY}" NAME)
    set(SDL3_DEST_PATH "${BUNDLE_PATH}/Contents/Frameworks/libSDL3.dylib")
    if(NOT SDL3_COPIED_NAME STREQUAL "libSDL3.dylib")
      file(RENAME "${BUNDLE_PATH}/Contents/Frameworks/${SDL3_COPIED_NAME}" "${SDL3_DEST_PATH}")
    endif()
  else()
    message(WARNING "SDL3_LIBRARY='${SDL3_LIBRARY}' does not exist, skipping")
  endif()
endif()
