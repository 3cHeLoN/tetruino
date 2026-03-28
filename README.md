# Tetruino

Build instructions (Linux):

1. Install dependencies (Ubuntu/Debian):

```bash
sudo apt update
sudo apt install build-essential cmake pkg-config libsdl2-dev libsdl2-mixer-dev
```

2. Build with CMake:

```bash
mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

3. Run:

```bash
./build/tetruino
```

Notes:
- This project uses `pkg-config` to find SDL2 and SDL2_mixer. If you have SDL installed in a custom location, set `PKG_CONFIG_PATH` accordingly.
- If you prefer to use `make` directly, you can still compile using the existing g++ task in your editor.
