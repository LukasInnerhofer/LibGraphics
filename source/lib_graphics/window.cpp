#include <cassert>
#include <map>
#include <memory>
#include <queue>
#include <stdexcept>

#include "lib_graphics/window.h"
#include "lib_graphics/string.h"
#include "window_impl.h"

namespace LibGraphics
{

static char const *vertexShaderSource {
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
    
    "out vec4 vertexColor;\n"

    "void main()\n"
    "{\n"
    "   gl_Position = vec4(position, 1.0);\n"
    "   vertexColor = vec4(color, 1.0);\n"
    "}"
};

static char const *fragmentShaderSource {
    "#version 330 core\n"
    "in vec4 vertexColor;\n"
    "out vec4 fragmentColor;\n"

    "void main()\n"
    "{\n"
        "fragmentColor = vertexColor;\n"
    "}"
};

static std::map<VertexBuffer::Primitive, GLenum> const primitiveMap {
    { VertexBuffer::Primitive::Triangle, GL_TRIANGLES },
    { VertexBuffer::Primitive::Quad, GL_QUADS }
};

class Window::Impl
{
public:
    void buildShaderProgram()
    {
        int success;
        std::vector<char> infoLog;
        GLint infoLogLength;

        vertexShader = openGl->glCreateShader()(GL_VERTEX_SHADER);
        openGl->glShaderSource()(vertexShader, 1, &vertexShaderSource, nullptr);
        openGl->glCompileShader()(vertexShader);
        openGl->glGetShaderiv()(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            openGl->glGetShaderiv()(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
            infoLog.resize(infoLogLength + 1);
            openGl->glGetShaderInfoLog()(vertexShader, infoLogLength, nullptr, &*infoLog.begin());
            throw std::runtime_error{
                std::string{"LibGraphics::Window Error. Failed to compile vertex shader.\n"}
                .append(infoLog.data())
            };
        }

        fragmentShader = openGl->glCreateShader()(GL_FRAGMENT_SHADER);
        openGl->glShaderSource()(fragmentShader, 1, &fragmentShaderSource, nullptr);
        openGl->glCompileShader()(fragmentShader);
        openGl->glGetShaderiv()(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            openGl->glGetShaderiv()(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
            infoLog.resize(infoLogLength + 1);
            openGl->glGetShaderInfoLog()(fragmentShader, infoLogLength, nullptr, &*infoLog.begin());
            throw std::runtime_error{
                std::string{"LibGraphics::Window Error. Failed to compile fragment shader.\n"}
                .append(infoLog.data())
            };
        }

        shaderProgram = openGl->glCreateProgram()();
        openGl->glAttachShader()(shaderProgram, vertexShader);
        openGl->glAttachShader()(shaderProgram, fragmentShader);
        openGl->glLinkProgram()(shaderProgram);
        openGl->glGetProgramiv()(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            openGl->glGetProgramiv()(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
            infoLog.resize(infoLogLength + 1);
            openGl->glGetProgramInfoLog()(shaderProgram, infoLogLength, nullptr, &*infoLog.begin());
            throw std::runtime_error{
                std::string{"LibGraphics::Window Error. Failed to link shader program.\n"}
                .append(infoLog.data())
            };
        }
    }

    WindowImpl osImpl;
    std::shared_ptr<OpenGl> openGl;
    std::shared_ptr<std::queue<Window::Event>> events{new std::queue<Window::Event>{}};
    std::map<VertexBuffer const *, GLuint> vertexBuffers;
    
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint vertexArray;
};

Window::Window(String const &title) : 
    m_pImpl{new Impl{}}
{
    m_pImpl->osImpl.create(title, m_pImpl->events);
    m_pImpl->openGl = m_pImpl->osImpl.getOpenGl();

    m_pImpl->buildShaderProgram();

    m_pImpl->openGl->glGenVertexArrays()(1, &m_pImpl->vertexArray);
}

Window::~Window()
{

}

bool Window::isOpen() const
{
    return m_pImpl->osImpl.isOpen();
}

bool Window::pollEvent(Window::Event &event)
{
    m_pImpl->osImpl.pollEvents();

    if (m_pImpl->events->size() > 0)
    {
        event = m_pImpl->events->front();
        return true;
    }
    return false;
}

void Window::clear(Color const &color)
{
    if (!isOpen())
    {
        return;
    }

    if (!m_pImpl->openGl->glClearColorSupported() ||
        !m_pImpl->openGl->glClearSupported())
    {
        throw std::runtime_error{"LibGraphics::Window::clear Error. Your system is missing support for required OpenGL functions."};
    }

    const Color::Float floatColor{color.toFloat()};
    if (!m_pImpl->openGl->isCurrent())
    {
        m_pImpl->openGl->makeCurrent();
    }
    m_pImpl->openGl->glClearColor()(floatColor.r, floatColor.g, floatColor.b, floatColor.a);
    m_pImpl->openGl->glClear()(GL_COLOR_BUFFER_BIT);
}

void Window::draw(VertexBuffer const &vertexBuffer)
{
    if (!isOpen())
    {
        return;
    }

    m_pImpl->openGl->glUseProgram()(m_pImpl->shaderProgram);

    GLuint glVertexBuffer;
    if (!m_pImpl->vertexBuffers.contains(&vertexBuffer))
    {
        m_pImpl->openGl->glGenBuffers()(1, &glVertexBuffer);
        m_pImpl->openGl->glBindBuffer()(GL_ARRAY_BUFFER, glVertexBuffer);
        m_pImpl->openGl->glBindVertexArray()(m_pImpl->vertexArray);
        m_pImpl->openGl->glVertexAttribPointer()(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(0));
        m_pImpl->openGl->glEnableVertexAttribArray()(0);
        m_pImpl->openGl->glVertexAttribPointer()(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
        m_pImpl->openGl->glEnableVertexAttribArray()(1);
        m_pImpl->vertexBuffers[&vertexBuffer] = glVertexBuffer;
    }
    else
    {
        glVertexBuffer = m_pImpl->vertexBuffers[&vertexBuffer];
    }

    m_pImpl->openGl->glBindBuffer()(GL_ARRAY_BUFFER, glVertexBuffer);
    m_pImpl->openGl->glBindVertexArray()(m_pImpl->vertexArray);
    
    std::vector<float> const &vertexData{vertexBuffer.getData()};
    m_pImpl->openGl->glBufferData()(
        GL_ARRAY_BUFFER, 
        vertexData.size() * sizeof(float),
        vertexData.data(),
        GL_STATIC_DRAW); // TODO: Determine draw type from drawables vertex buffer
    
    m_pImpl->openGl->glDrawArrays()(
        primitiveMap.at(vertexBuffer.getPrimitive()),
        0,
        static_cast<GLsizei>(vertexBuffer.getCount()));
}

void Window::display() const
{
    if (!isOpen())
    {
        return;
    }

    m_pImpl->osImpl.display();
}

void Window::close()
{
    if (!isOpen())
    {
        return;
    }

    m_pImpl->openGl->glDeleteShader()(m_pImpl->vertexShader);
    m_pImpl->openGl->glDeleteShader()(m_pImpl->fragmentShader);
    m_pImpl->openGl->glDeleteProgram()(m_pImpl->shaderProgram);

    // If we stored VBOs contiguously we could delete them with one call :^)
    for (std::pair<VertexBuffer const *, GLuint> vertexBuffer : m_pImpl->vertexBuffers)
    {
        m_pImpl->openGl->glDeleteBuffers()(1, &vertexBuffer.second);
    }
    m_pImpl->vertexBuffers.clear();

    m_pImpl->openGl->glDeleteVertexArrays()(1, &m_pImpl->vertexArray);

    m_pImpl->osImpl.close();
}

}

