#include "app.h"

#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)

static const char* GetCompilerVersion()
{
#if defined(_MSC_VER)
    return "MSVC " STRINGIZE(_MSC_FULL_VER);
#elif defined(__clang__)
    return __VERSION__;
#elif defined(__GNUC__)
    return __VERSION__;
#else
    return "Unknown compiler";
#endif
}

void Engine::App::run(std::string filepath, int height, int width, std::string name)
{
    if (!glfwInit())
    {
        spdlog::error("Failed to initialize GLFW");
        return;
    }

    spdlog::info("GLFW initialized successfully");

    Window window{height, width, name};
    window.setProperties();
    window.createWindow();

    if (!glewInit())
    {
        spdlog::error("Failed to initialize GLEW");
        return;
    }

    spdlog::info("GLEW initialized successfully");

    const char* gpuVendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    const char* gpuRenderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    const char* glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    const char* glslVersion = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

    spdlog::info("GPU Vendor: {}", gpuVendor ? gpuVendor : "Unknown");
    spdlog::info("GPU Renderer: {}", gpuRenderer ? gpuRenderer : "Unknown");
    spdlog::info("OpenGL Version: {}", glVersion ? glVersion : "Unknown");
    spdlog::info("GLSL Version: {}", glslVersion ? glslVersion : "Unknown");
    spdlog::info("Compiler Version: {}", GetCompilerVersion());

    Chunks chunks{};
    VertexBuffer vertexbuffer{chunks.cubeGeometry, sizeof(chunks.cubeGeometry)};
    IndexBuffer indexbuffer{chunks.cubeConnectivity, sizeof(chunks.cubeConnectivity)};

    loadTexture("/home/lames/Documents/Engine/assets/dirt.png");

    VertexArray vertexArray{};
    vertexArray.Bind();
    vertexArray.LinkAttrib(0, 8 * sizeof(GL_FLOAT), 0);
    vertexArray.Bind();
    vertexArray.LinkAttrib(1, 8 * sizeof(GL_FLOAT), (3 * sizeof(GL_FLOAT)));
    vertexArray.Bind();
    vertexArray.LinkAttrib(2, 8 * sizeof(GL_FLOAT), (6 * sizeof(GL_FLOAT)));

    Shader shader{filepath};

    shader.ParseShaders();
    shader.CompileShaders();

    Render render;
    window.loop(render, vertexbuffer, indexbuffer, shader, chunks);
}

void Engine::App::loadTexture(const char *filepath)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int texWidth, texHeight, nrChannels;
    unsigned char *data = stbi_load(filepath, &texWidth, &texHeight, &nrChannels, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        const char *formatName = "RGB";
        if (nrChannels == 1)
        {
            format = GL_RED;
            formatName = "RED";
        }
        else if (nrChannels == 3)
        {
            format = GL_RGB;
            formatName = "RGB";
        }
        else if (nrChannels == 4)
        {
            format = GL_RGBA;
            formatName = "RGBA";
        }
        else
        {
            spdlog::warn("Texture '{}' has {} channels; using RGB format", filepath, nrChannels);
        }

        spdlog::info("Loaded texture '{}' [id={}, {}x{}, channels={}, format={}]",
                     filepath, texture, texWidth, texHeight, nrChannels, formatName);
        glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        spdlog::error("Failed to load texture '{}'", filepath);
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, texture);
}
