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
	@$(CMAKE) -S . -B $(BUILD_DIR) -G $(GENERATOR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build: configure
	@$(CMAKE) --build $(BUILD_DIR)

run: build
	@./$(BUILD_DIR)/mario_isn.app/Contents/MacOS/mario_isn

clean:
	@rm -rf $(BUILD_DIR)