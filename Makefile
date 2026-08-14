# Inclusion optionnelle du Makefile.local pour commande make privé
-include Makefile.local

# Variables
BUILD_DIR = build
CMAKE = cmake
GENERATOR = Ninja
BUILD_TYPE = Debug

.PHONY: all configure build run clean

# Commande par défaut
all: build

configure:
	@$(CMAKE) -S . -B $(BUILD_DIR) -G $(GENERATOR) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		$(if $(ARCH),-DCMAKE_OSX_ARCHITECTURES="$(ARCH)") \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		$(EXTRA_CMAKE_ARGS)

build: configure
	@$(CMAKE) --build $(BUILD_DIR)

run: build
	@./$(BUILD_DIR)/mario_isn.app/Contents/MacOS/mario_isn

clean:
	@rm -rf $(BUILD_DIR)

prod-arm:
	$(MAKE) BUILD_DIR=build-arm BUILD_TYPE=Release ARCH="arm64" configure build

prod-linux:
	$(MAKE) BUILD_DIR=build-linux BUILD_TYPE=Release GENERATOR="Ninja" configure build

# Cross-build for Intel from an Apple Silicon host: clang -arch x86_64 needs
# no Rosetta to compile, but Homebrew's arm64 prefix (/opt/homebrew) only has
# arm64 SDL2 libs. A second, x86_64 Homebrew installed under Rosetta at
# /usr/local provides the x86_64 SDL2 CMake configs pointed to below.
prod-intel:
	$(MAKE) BUILD_DIR=build-intel BUILD_TYPE=Release ARCH="x86_64" \
		EXTRA_CMAKE_ARGS='-DSDL2_DIR=/usr/local/lib/cmake/SDL2 -DSDL2_image_DIR=/usr/local/lib/cmake/SDL2_image -DSDL2_mixer_DIR=/usr/local/lib/cmake/SDL2_mixer -DSDL3_DIR=/usr/local/lib/cmake/SDL3' \
		configure build

# # Ne fonctionne pas encore
# prod-macos:
# 	$(MAKE) BUILD_DIR=build-macos BUILD_TYPE=Release ARCH="universal" configure build
