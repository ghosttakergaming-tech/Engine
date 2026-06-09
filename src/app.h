#pragma once

#include "stb_image.h"
#include "include/spdlog/spdlog.h"

#include "shader.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "render.h"
#include "window.h"
#include "chunks.h"

namespace Engine {
    class App {
        public:
            void run(std::string filepath, int height, int width, std::string name);
            void loadTexture(const char* filepath); 
    };
}