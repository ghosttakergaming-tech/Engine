#include "app.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "include/spdlog/spdlog.h"

using namespace Engine;

int main() {
    spdlog::info("Starting engine...");

    App app{};

    app.run(SHADER_FILE, 1280, 720, "Engine");

    spdlog::info("Shutting down...");

    return 0;
}

