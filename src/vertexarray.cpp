#include "vertexarray.h"
#include "include/GL/glew.h"

Engine::VertexArray::VertexArray()
{
    glGenVertexArrays(1, &renderId);
}

Engine::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &renderId);
}

void Engine::VertexArray::LinkAttrib(unsigned int index, unsigned int stride, unsigned long offset)
{
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (const void*) offset); 
    glEnableVertexAttribArray(index);
}

void Engine::VertexArray::Bind() {
    glBindVertexArray(renderId);
}

void Engine::VertexArray::Unbind() {
    glBindVertexArray(0);
}
