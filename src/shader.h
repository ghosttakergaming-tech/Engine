#pragma once

#include "iostream"

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/spdlog/spdlog.h"

namespace Engine {

    enum class ShaderType {
        None,
        VertexShader,
        FragmentShader
    };
    
    struct ShaderCode {
        std::string vertCode;
        std::string fragCode;
    };

    class Shader {
        public:
            Shader(std::string filepath);
            ~Shader();

            void ParseShaders();
            void CompileShaders();
            void UseShaders();
            unsigned int getProgram();
            void setUniform4f(std::string name, float v1, float v2, float v3, float v4);
            void setUniformMat4f(std::string name, glm::mat4 value);
            void setUniformVec3(std::string name, glm::vec3 value);
            void setUniformVec2(std::string name, glm::vec2 value);
        private:
            std::string filepath;

            unsigned int vertexShader;
            unsigned int fragmentShader;
            unsigned int shaderProgram;
            
            std::string vertShaderCode;
            std::string fragShaderCode;

            void TestShaders(unsigned int shader);
    };
}