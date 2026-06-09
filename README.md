# Voxel Engine

A real-time 3D voxel engine built with C++, OpenGL, and CMake. Generates infinite procedural terrain using Perlin noise and renders visible blocks efficiently using GPU instancing.

---

## Features

- Procedural terrain generation with Perlin noise
- Smart face culling - only renders surface blocks
- GPU instanced rendering for performance
- Dynamic chunk loading as you explore
- First-person camera with mouse look
- Custom OpenGL shader pipeline

---

## Requirements

- CMake 3.10+
- C++17 compiler
- OpenGL 4.6 compatible GPU
- All dependencies (GLFW, GLEW, GLM, FastNoiseLite, stb_image) bundled in `src/include/`

---

## Build & Run

```bash
cd /home/lames/Documents/Engine
mkdir -p build && cd build
cmake ..
make
./Engine
```

---

## Controls

- **WASD** - Move
- **Mouse** - Look around
- **ESC** - Release cursor

---

## How It Works

1. Perlin noise determines which blocks are stone vs air
2. Surface blocks (with at least one air neighbor) are kept
3. Buried blocks are culled to save memory
4. All visible blocks rendered in a single GPU instanced call
5. Chunks regenerate when player moves far enough

---

## Project Structure

```
src/
├── main.cpp
├── app.cpp/h           # Application setup
├── window.cpp/h        # Window & input
├── camera.cpp/h        # Camera system
├── chunks.cpp/h        # Terrain generation
├── render.cpp/h        # Rendering
├── shader.cpp/h        # Shader handling
├── vertexbuffer.cpp/h
├── vertexarray.cpp/h
├── indexbuffer.cpp/h
├── shaders/
│   └── shader.shader
└── include/            # Dependencies & textures
```

---

## License

See LICENSE file.
