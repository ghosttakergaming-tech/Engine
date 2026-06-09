#include "vertexbuffer.h"
#include "include/GL/glew.h"

Engine::VertexBuffer::VertexBuffer(float data[], unsigned int size)
{
    glGenBuffers(1, &renderId); 
    glBindBuffer(GL_ARRAY_BUFFER, renderId);  
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Engine::VertexBuffer::VertexBuffer(glm::vec3 *data, unsigned int size)
{
    glGenBuffers(1, &renderId); 
    glBindBuffer(GL_ARRAY_BUFFER, renderId);  
    glBufferData(GL_ARRAY_BUFFER, size, &data[0], GL_STATIC_DRAW);
}

Engine::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &renderId);
}

void Engine::VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, renderId); 
}

void Engine::VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}
