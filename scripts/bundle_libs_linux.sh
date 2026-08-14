#!/usr/bin/env bash
# Copies the non-system shared libraries an executable depends on (SDL2 and
# its transitive deps) next to it and rewrites its rpath, so the binary runs
# on a machine without those libs installed system-wide. Best-effort: if
# `patchelf` isn't available (e.g. a plain local dev build), it warns and
# leaves the build untouched rather than failing it.
set -euo pipefail

EXE="$1"
LIBDIR="$2"

if ! command -v patchelf >/dev/null 2>&1; then
  echo "warning: patchelf not found, skipping SDL2 lib bundling (dev build only)" >&2
  exit 0
fi

mkdir -p "$LIBDIR"

# Base OS/libc/toolchain libraries that must come from the target system,
# never be bundled.
SYSTEM_LIB_PATTERN='^(linux-vdso|ld-linux|libc\.|libm\.|libdl\.|libpthread\.|librt\.|libgcc_s\.|libstdc\+\+\.|libselinux\.|libresolv\.)'

copy_deps() {
  local target="$1"
  local libs
  # ldd/awk may legitimately produce zero matching lines (e.g. a leaf lib with
  # no further non-system deps) -- `|| true` keeps that from tripping
  # pipefail/set -e; a single awk filter (vs. piping into grep) avoids grep's
  # own "no match" exit status doing the same.
  libs=$(ldd "$target" 2>/dev/null | awk '$3 ~ /^\// {print $3}') || true
  [ -z "$libs" ] && return 0
  while IFS= read -r lib; do
    [ -z "$lib" ] && continue
    base="$(basename "$lib")"
    if echo "$base" | grep -Eq "$SYSTEM_LIB_PATTERN"; then
      continue
    fi
    dest="$LIBDIR/$base"
    if [ ! -f "$dest" ]; then
      cp -L "$lib" "$dest"
      chmod u+w "$dest"
      patchelf --set-rpath '$ORIGIN' "$dest"
      copy_deps "$dest"
    fi
  done <<< "$libs"
}

copy_deps "$EXE"
patchelf --set-rpath '$ORIGIN/lib' "$EXE"
