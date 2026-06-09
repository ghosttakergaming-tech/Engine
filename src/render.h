#pragma once

#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "shader.h"
#include "chunks.h"
#include "camera.h"

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

#include "include/GL/glew.h"
#include "include/glfw3.h"

namespace Engine {

    class Chunks;

    class Render {
        public:
            void draw(int height, int width, glm::mat4 camera,VertexBuffer &vb, IndexBuffer &ib, Shader &shader, Chunks &chunks);
    };
}