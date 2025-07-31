#!/bin/bash
# Complete script to compile ANTLR4 as WebAssembly static library

# 1. Clone ANTLR4 repository
echo "Cloning ANTLR4 repository..."
git clone https://github.com/antlr/antlr4.git
cd antlr4
git checkout 4.13.2
cd runtime/Cpp

# 2. Create build directory
echo "Creating build directory..."
mkdir build-wasm && cd build-wasm

# 3. Configure and compile
echo "Configuring with emcmake..."
emcmake cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DANTLR4_INSTALL=ON \
  -DWITH_LIBCXX=OFF \
  -DANTLR4_USE_THREAD_LOCAL_CACHE=OFF \
  -DCMAKE_CXX_STANDARD=17

echo "Compiling with emmake..."
emmake make -j4

echo "ANTLR4 WebAssembly static library compilation completed!"
echo "Static library location: $(pwd)/runtime/libantlr4-runtime.a"
echo "Build process finished successfully."
