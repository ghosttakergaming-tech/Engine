#pragma once

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/spdlog/spdlog.h"

namespace Engine {
    class VertexBuffer {
        public:
            VertexBuffer(float data[], unsigned int size);
            VertexBuffer(glm::vec3 *data, unsigned int size);
            ~VertexBuffer();

            void Bind();
            void Unbind();

        private:
            unsigned int renderId;
    };
}