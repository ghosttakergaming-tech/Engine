#pragma once

#include "vertexbuffer.h"
#include "include/GL/glew.h"

namespace Engine {
    class VertexArray {
        public:
            VertexArray();
            ~VertexArray();

            void LinkAttrib(unsigned int index, unsigned int stride, unsigned long offset);
            void Bind();
            void Unbind();
        private:
            unsigned int renderId;
    };
}