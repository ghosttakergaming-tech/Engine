#pragma once

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

#include "include/GL/glew.h"
#include "include/glfw3.h"

namespace Engine {
    class Camera {
        public:
            Camera();

            inline static glm::vec3 direction;
            inline static bool firstMouse = true;
            inline static float yaw;
            inline static float pitch;
            
            inline static double lastX;
            inline static double lastY;

            glm::mat4 getView();
            static glm::vec3 getCameraPos();
            glm::vec3 getCameraUp();
            glm::vec3 getCameraFront();

            void setCameraPos(glm::vec3 cameraPos);
            void setCameraFront(glm::vec3 cameraPos);
            static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        private:
            inline static glm::vec3 cameraPos   = glm::vec3(0.0f, 20.0f,  0.0f);
            glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
            glm::mat4 view;
    };
}