#include "window.h"

Engine::Window::Window(int height, int width, std::string name)
{
    this->height = height;
    this->width = width;
    this->name = name;
}

Engine::Window::~Window()
{
    glfwTerminate();
    spdlog::info("Window destroyed successfully");
}

void Engine::Window::createWindow()
{
    if((window = glfwCreateWindow(height, width, name.c_str(), NULL, NULL)) == nullptr)
    {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    spdlog::info("Window created successfully: address={}, height={}, width={}, name={}", static_cast<const void*>(window), height, width, name);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwSetCursorPosCallback(window, camera.mouse_callback);
    glfwSetFramebufferSizeCallback(window, Engine::Window::framebuffer_size_callback);  

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Engine::Window::setProperties()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Engine::Window::loop(Render render, VertexBuffer &vb, IndexBuffer &ib, Shader &shader, Chunks &chunks)
{
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);

        render.draw(height, width, camera.getView(), vb, ib, shader, chunks);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
        processInput(window);
    }

    glfwTerminate();
}

void Engine::Window::processInput(GLFWwindow *window)
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;  

    float cameraSpeed = 2.5f * deltaTime;  // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.setCameraPos(camera.getCameraPos() + (cameraSpeed * camera.getCameraFront()));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.setCameraPos(camera.getCameraPos() - (cameraSpeed * camera.getCameraFront()));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.setCameraPos(camera.getCameraPos() - (glm::normalize(glm::cross(camera.getCameraFront(), camera.getCameraUp())) * cameraSpeed));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.setCameraPos(camera.getCameraPos() + (glm::normalize(glm::cross(camera.getCameraFront(), camera.getCameraUp())) * cameraSpeed));
    
    camera.setCameraFront(glm::normalize(Engine::Camera::direction));
}


void Engine::Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
