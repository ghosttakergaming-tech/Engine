#pragma once

#include <map>
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/FastNoiseLite.h"
#include "include/spdlog/spdlog.h"

#include <vector>
#include <memory>
#include <random>

#include "render.h"
#include "vertexbuffer.h"
#include "vertexarray.h"
#include "camera.h"

namespace Engine {
    class Chunks {
        public:

        Chunks();
        ~Chunks();

        void GenChunks(Shader shader);

        float cubeGeometry[228] = {
            // Front face
            -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Bottom-left
             0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom-right
            -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Top-left
             0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Top-right

            // Back face
             0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Bottom-left
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom-right
             0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Top-left
            -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Top-right

            // Left face
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Bottom-left
            -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom-right
            -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Top-left
            -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Top-right

            // Right face
             0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Bottom-left
             0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom-right
             0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Top-left
             0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Top-right

            // Top face
            -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Bottom-left
             0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom-right
            -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Top-left
             0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Top-right

            // Bottom face
             0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Bottom-left
            -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom-right
             0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Top-left
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f  // Top-right
        };

        unsigned int cubeConnectivity[36] = {
            0, 1, 2, 
            2, 1, 3,

            4, 5, 6, 
            6, 5, 7,	

            8, 9,10, 
            10, 9,11,

            12,13,14, 
            14,13,15,

            16,17,18, 
            17,19,18,

            20,21,22, 
            21,23,22
       };
       private:

       void createChunk(int xt, int zt);

       std::vector<glm::vec3> chunkCubes;
       glm::vec3 playerPos = Camera::getCameraPos();
       glm::vec3 lastPlayerPos = playerPos;
       VertexArray instanceArray{};
       std::mt19937 mt{};

       std::unordered_map<uint64_t, std::pair<std::unique_ptr<VertexBuffer>, int>> chunkMap;
       int playerChunkX = std::floor(playerPos.x / chunkSize);
       int playerChunkZ = std::floor(playerPos.z / chunkSize);

       FastNoiseLite noise;
       int renderDistance = 4;
       bool needToUpdate = true;
       float offset = 1.0f;
       uint64_t chunkId = 0;
       const int chunkSize = 16;

       enum class BlockState {
        AIR,
        STONE
       };

       BlockState getBlock(int x, int y, int z);
       bool isAirNextToBlock(int x, int y, int z);
    };
}