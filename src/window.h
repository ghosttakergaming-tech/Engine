#pragma once

#include <string>
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "shader.h"
#include "render.h"
#include "include/glfw3.h"
#include "camera.h"
#include "chunks.h"

namespace Engine {
    class Window {
        public:
            Window(int height, int width, std::string name);
            ~Window();
            
            void createWindow();
            void setProperties();
            void loop(Render render, VertexBuffer &vb, IndexBuffer &ib, Shader &shader, Chunks &chunks);
            static void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
        private:
            GLFWwindow* window;

            int width;
            int height;
            std::string name;

            float deltaTime = 0.0f;	// Time between current frame and last frame
            float lastFrame = 0.0f; // Time of last frame

            void processInput(GLFWwindow *window);

            Engine::Camera camera;
    };
}