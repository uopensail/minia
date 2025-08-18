# Compiler settings
CXX = emcc
CXXFLAGS = -std=c++17 -O2 -fPIC

# Get current directory
PROJECT_ROOT := $(abspath $(CURDIR)/..)

# Path settings
SRC_DIR = $(PROJECT_ROOT)/src
LIB_DIR = $(PROJECT_ROOT)/lib
BUILD_DIR = $(PROJECT_ROOT)/build
ANTLR4_LIB = $(PROJECT_ROOT)/webassembly/antlr4/runtime/Cpp/dist/libantlr4-runtime.a
ANTLR4_INCLUDE = $(PROJECT_ROOT)/webassembly/antlr4/runtime/Cpp/runtime/src

# Source files
GRAMMAR_SOURCES = $(wildcard $(SRC_DIR)/grammar/*.cpp $(SRC_DIR)/grammar/*.cc)
MAIN_SOURCES = $(PROJECT_ROOT)/src/builtin.cc $(PROJECT_ROOT)/src/common.cc $(PROJECT_ROOT)/src/jsminia.cc \
    $(PROJECT_ROOT)/src/minia.cc $(PROJECT_ROOT)/src/MurmurHash3.cc

SOURCES = $(MAIN_SOURCES) $(GRAMMAR_SOURCES)

MAIN_HEADERS = $(PROJECT_ROOT)/include
GRAMMAR_HEADERS = $(PROJECT_ROOT)/include/grammar

# Library settings
LIB_NAME = minia
WASM_JS = $(LIB_DIR)/$(LIB_NAME).js

# EMSCRIPTEN_BINDINGS specific WASM options
WASM_FLAGS = -s WASM=1 \
             -s MODULARIZE=1 \
             -s EXPORT_NAME='JSMinia' \
             -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
             -s ALLOW_MEMORY_GROWTH=1 \
             -s INITIAL_MEMORY=2MB \
             -s FILESYSTEM=0 \
             -s SINGLE_FILE=1 \
             -s ENVIRONMENT=web \
             --closure 1 \
             --bind

# Default target
all: info $(WASM_JS)

# Display build information
info:
	@echo "=== WebAssembly Static Library Build Information ==="
	@echo "Project root directory: $(PROJECT_ROOT)"
	@echo "Source directory: $(SRC_DIR)"
	@echo "Library output directory: $(LIB_DIR)"
	@echo "Static library: $(STATIC_LIB)"
	@echo "WASM library: $(WASM_LIB)"
	@echo "Number of source files: $(words $(SOURCES))"
	@echo "=================================================="

$(WASM_JS): $(SOURCES) | $(LIB_DIR)
	@echo "Compiling all source files to WebAssembly..."
	@echo "Source files:"
	@for src in $(SOURCES); do echo "  $$src"; done
	$(CXX) $(CXXFLAGS) $(WASM_FLAGS) \
		-I$(ANTLR4_INCLUDE) \
		-I$(MAIN_HEADERS) \
        -I$(GRAMMAR_HEADERS) \
		$(SOURCES) \
		$(ANTLR4_LIB) \
		-o $@
	@echo "✅ Compilation completed: $@"

# Create necessary directories
$(LIB_DIR):
	mkdir -p $@

# Clean build artifacts
clean:
	rm -rf $(LIB_DIR)

.PHONY: all clean info
