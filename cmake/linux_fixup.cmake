# cmake/linux_fixup.cmake
cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED APP_DIR)
  message(FATAL_ERROR "linux_fixup: APP_DIR not set")
endif()

set(outdir "${APP_DIR}/lib")
file(MAKE_DIRECTORY "${outdir}")

set(exe "${APP_DIR}/mario_isn")

# 1) Copier les 3 libs SDL2 (SONAME réels) utilisées par l’exe
execute_process(
  COMMAND /bin/sh -lc
          "ldd \"${exe}\" \
             | awk '/libSDL2/ {print $3}' \
             | xargs -r -I{} cp -f {} \"${outdir}\""
  RESULT_VARIABLE rc1
)

if(NOT rc1 EQUAL 0)
  message(WARNING "linux_fixup: ldd SDL2 copy step returned ${rc1}")
endif()

# 2) (Optionnel) Copier quelques dépendances 'feuilles' fréquentes (image/son)
execute_process(
  COMMAND /bin/sh -lc
          "ldd \"${exe}\" \
             | awk '{print $3}' \
             | grep -E '/lib(webp|png|jxl|jpeg|tiff|ogg|vorbis|opus|FLAC).*\\.so' \
             | xargs -r -I{} cp -n {} \"${outdir}\""
  RESULT_VARIABLE rc2
)
