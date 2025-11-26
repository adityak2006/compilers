# Project Overview

This project implements the core components of a compiler pipeline, including lexical analysis, parsing, semantic analysis, and code generation. The objective is to design a robust and modular system that translates source input into an optimized target representation. 

---

# Build Instructions
---

Make sure to run these inside the project.

## macOS

### 1. Install dependencies

```sh
brew update
brew install cmake ninja llvm flex bison
```

### 2. Configure

```sh
mkdir -p build
cd build
cmake -G Ninja \
  -DMLIR_DIR="$(brew --prefix llvm)/lib/cmake/mlir" \
  ..
```

### 3. Build

```sh
cmake --build . -- -j$(sysctl -n hw.ncpu)
```

### 4. Create Input file inside the build directory
```sh
touch input.txt
```
Edit the file as necessary. Make sure it is named as input.txt

### 5. Run on input.txt

```sh
./my_compiler
```

---

##  Linux (Ubuntu / Debian)

**Note**: Many distros do not include MLIR. If missing, see the [Build LLVM + MLIR manually](#build-llvm--mlir-manually) section below.

### 1. Install dependencies

```sh
sudo apt update
sudo apt install -y build-essential cmake ninja-build flex bison
sudo apt install -y llvm-dev libmlir-dev || true
```
### 2. Configure

```sh
mkdir -p build
cd build
cmake -G Ninja \
  -DMLIR_DIR="$(brew --prefix llvm)/lib/cmake/mlir" \
  ..
```

### 3. Build

```sh
cmake --build . -- -j$(sysctl -n hw.ncpu)
```

### 4. Create Input file inside the build directory
```sh
touch input.txt
```
Edit the file as necessary. Make sure it is named as input.txt

### 5. Run on input.txt

```sh
./my_compiler
```

---
## Build LLVM + MLIR manually

If your distribution does not provide MLIR packages, you'll need to build LLVM and MLIR from source. Instructions can be found in the [LLVM documentation](https://llvm.org/docs/GettingStarted.html).
