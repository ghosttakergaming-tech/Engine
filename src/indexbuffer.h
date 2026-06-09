#pragma once
#include "include/spdlog/spdlog.h"

namespace Engine {
    class IndexBuffer {
        public:
            IndexBuffer(unsigned int data[], unsigned int size);
            ~IndexBuffer();

            void Bind();
            void Unbind();
        private:
            unsigned int renderId;
    };
}