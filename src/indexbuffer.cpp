#include "indexbuffer.h"
#include "include/GL/glew.h"

Engine::IndexBuffer::IndexBuffer(unsigned int data[], unsigned int size)
{
    glGenBuffers(1, &renderId); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderId);  
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Engine::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &renderId);
}

void Engine::IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderId); 
}

void Engine::IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}
