#include "shader.h"
#include "include/GL/glew.h"
#include <sstream>
#include <fstream>
#include <iostream>

Engine::Shader::Shader(std::string filepath)
{
    this->filepath = filepath;
}

Engine::Shader::~Shader()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(shaderProgram);
}

void Engine::Shader::ParseShaders()
{
    spdlog::info("Parsing shaders from file: {}", filepath);
    std::ifstream source(filepath);
    ShaderType shaderType = ShaderType::None;

    std::string line;

    while (getline(source, line)) {
        if (line == "#VertexShader") {
            shaderType = ShaderType::VertexShader;
        } 
        
        if (line == "#FragShader") {
            shaderType = ShaderType::FragmentShader;
        }

        if (line != "#VertexShader" && line != "#FragShader") {    
            if (shaderType == ShaderType::VertexShader) {
                vertShaderCode += line += '\n';
            } else if (shaderType == ShaderType::FragmentShader) {
                fragShaderCode += line += '\n';
            }
        }
    }

    source.close();
}

void Engine::Shader::CompileShaders()
{
    const char* code;
    spdlog::info("Compiling shaders");

    code = vertShaderCode.c_str();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &code, NULL);
    glCompileShader(vertexShader);

    code = fragShaderCode.c_str();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &code, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    TestShaders(vertexShader);
    TestShaders(fragmentShader);
    TestShaders(shaderProgram);
}

void Engine::Shader::UseShaders()
{
    glUseProgram(shaderProgram);
}

unsigned int Engine::Shader::getProgram()
{
    return shaderProgram;
}

void Engine::Shader::setUniform4f(std::string name, float v1, float v2, float v3, float v4)
{
    int location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform4f(location, v1, v2, v3, v4);
}

void Engine::Shader::setUniformMat4f(std::string name, glm::mat4 value)
{
    int location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniformMatrix4fv(location, 1, false, &value[0][0]);
}

void Engine::Shader::setUniformVec3(std::string name, glm::vec3 value)
{
    int location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform3fv(location, 1, &value[0]);
}

void Engine::Shader::setUniformVec2(std::string name, glm::vec2 value)
{
    int location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform2fv(location, 1, &value[0]);
}

void Engine::Shader::TestShaders(unsigned int shader)
{
    int success;
    char infoLog[512];
    spdlog::info("Testing shader: {}", shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        spdlog::error("Shader compilation failed: {}", infoLog);
    }
}
