#include "chunks.h"

Engine::Chunks::Chunks() {
   noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
   noise.SetSeed(mt());
   noise.SetFractalOctaves(4); 

   spdlog::info("Chunks System initialized successfully");
}

Engine::Chunks::~Chunks() {
    chunkCubes.clear();
    chunkMap.clear();
    spdlog::info("Chunks System destroyed successfully");
}


void Engine::Chunks::GenChunks(Shader shader)
{
    // Update player position every frame
    playerPos = Camera::getCameraPos();  

    if (glm::distance(playerPos.x, lastPlayerPos.x) >= 16.0f) {
        needToUpdate = true;
    }

    if (glm::distance(playerPos.z, lastPlayerPos.z) >= 16.0f) {
        needToUpdate = true;
    }

    if (needToUpdate) {
        playerChunkX = std::floor(playerPos.x / chunkSize);
        playerChunkZ = std::floor(playerPos.z / chunkSize);

        chunkCubes.clear();

        for (int xt = (playerChunkX - renderDistance); xt <= (playerChunkX + renderDistance); xt++) {
            for (int zt = (playerChunkZ - renderDistance); zt <= (playerChunkZ + renderDistance); zt++) {
                uint64_t keyX = static_cast<uint32_t>(xt);
                uint64_t keyZ = static_cast<uint32_t>(zt);
                chunkId = (keyX << 32) | keyZ;

                if (chunkMap.find(chunkId) == chunkMap.end()) {
                    chunkCubes.clear();
                    createChunk(xt, zt);
                    chunkMap.emplace(chunkId, std::make_pair(std::make_unique<VertexBuffer>(chunkCubes.data(), chunkCubes.size() * sizeof(glm::vec3)), chunkCubes.size()));
                }
            }
        }

        spdlog::info("Chunk update: playerPos=({:.2f}, {:.2f}, {:.2f}), playerChunk=({}, {}), needToUpdate={}, totalChunks={}",
            playerPos.x, playerPos.y, playerPos.z,
            playerChunkX, playerChunkZ,
            needToUpdate,
            chunkMap.size());

        lastPlayerPos = playerPos;
    }

    needToUpdate = false;

    shader.UseShaders();

    for(auto& [id, pair] : chunkMap) {
        uint64_t xt = static_cast<uint64_t>(id >> 32);
        uint64_t zt = static_cast<uint64_t>(id & 0xFFFFFFFF);

        if(std::abs((int)xt - playerChunkX) > renderDistance || std::abs((int)zt - playerChunkZ) > renderDistance) {
            continue;
        }

        pair.first->Bind();
        instanceArray.LinkAttrib(3, 3 * sizeof(float), 0);
        glVertexAttribDivisor(3, 1);

        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, pair.second);
    }
}

void Engine::Chunks::createChunk(int xt, int zt)
{
    for(int y = -16; y < 16; y++) {
        for(int z = zt * chunkSize; z < (zt + 1) * chunkSize; z++) {
            for(int x = xt * chunkSize; x < (xt + 1) * chunkSize; x++) {
                if(getBlock(x,y,z) != BlockState::AIR) {
                    if(isAirNextToBlock(x, y, z)) {
                        chunkCubes.emplace_back((float)x * offset, (float)y * offset, (float)z * offset);
                    }
                }
            }
        }
    }
}

Engine::Chunks::BlockState Engine::Chunks::getBlock(int x, int y, int z)
{
    if (y > 15)
    {
        return BlockState::AIR;
    }

    if (noise.GetNoise((float)x, (float)y, (float)z) > 0.0f)
    {
        return BlockState::STONE;
    }
    
    return BlockState::AIR;
};

bool Engine::Chunks::isAirNextToBlock(int x, int y, int z) {   
    if (getBlock(x + 1, y, z) == BlockState::AIR) return true;
    if (getBlock(x - 1, y, z) == BlockState::AIR) return true;
    if (getBlock(x, y + 1, z) == BlockState::AIR) return true;
    if (getBlock(x, y - 1, z) == BlockState::AIR) return true;
    if (getBlock(x, y, z + 1) == BlockState::AIR) return true;
    if (getBlock(x, y, z - 1) == BlockState::AIR) return true;
    return false;
}
