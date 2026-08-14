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
