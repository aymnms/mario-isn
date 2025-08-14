#!/usr/bin/env bash
set -euo pipefail
NEW="$1"
FILE="CMakeLists.txt"

# Utiliser -i.bak => OK sur GNU sed (Linux) et BSD sed (macOS)
sed -E -i.bak "s/(MACOSX_BUNDLE_SHORT_VERSION_STRING\s+\")([0-9A-Za-z\.-]+)(\")/\1${NEW}\3/" "$FILE"
sed -E -i.bak "s/(MACOSX_BUNDLE_BUNDLE_VERSION\s+\")([0-9A-Za-z\.-]+)(\")/\1${NEW}\3/" "$FILE"

# Nettoyage du fichier de sauvegarde créé par -i.bak
rm -f "${FILE}.bak"

echo "CMake version fields bumped to $NEW"
