#include "camera.h"

Engine::Camera::Camera()
{
    Engine::Camera::direction = glm::vec3(0.0f, 0.0f, -1.0f);
    Engine::Camera::yaw = -90.0f;
    Engine::Camera::firstMouse = true;
}

glm::mat4 Engine::Camera::getView()
{
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return view;
}

glm::vec3 Engine::Camera::getCameraPos()
{
    return cameraPos;
}

glm::vec3 Engine::Camera::getCameraUp()
{
    return cameraUp;
}

glm::vec3 Engine::Camera::getCameraFront()
{
    return cameraFront;
}

void Engine::Camera::setCameraPos(glm::vec3 cameraPos)
{
    this->cameraPos = cameraPos;
}

void Engine::Camera::setCameraFront(glm::vec3 cameraFront)
{
    this->cameraFront =  cameraFront;
}

void Engine::Camera::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}
