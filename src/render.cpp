#include "render.h"

void Engine::Render::draw(int height, int width, glm::mat4 camera, VertexBuffer &vb, IndexBuffer &ib, Shader &shader, Chunks &chunks)
{
    vb.Bind();
    ib.Bind();
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    view = camera;
    proj = glm::perspective(glm::radians(45.0f), (float) (height/width), 0.1f, 100.0f);

    shader.setUniformMat4f("model", model);
    shader.setUniformMat4f("view", view);
    shader.setUniformMat4f("proj", proj);

    shader.UseShaders();

    chunks.GenChunks(shader);
}
