#include "Shader.h"
#include "util/logger.h"

// For compilation/linking logs
#include <vector>
// Loading from files
#include <fstream>
#include <sstream>

namespace Gfx
{

Shader::Shader()
{
    programId = glCreateProgram();
}

Shader::~Shader()
{
    glDeleteProgram(programId);
}

Shader& Shader::addStage(GLenum stage, const char* source)
{
    GLuint shader = glCreateShader(stage);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint result = GL_FALSE; 
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result != GL_FALSE)
    {
        // Compilation successful
        glAttachShader(programId, shader);
    }
    else
    {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength + 1);
        glGetShaderInfoLog(shader, logLength, &logLength, log.data());
        log[logLength] = '\0'; // Guard against bad implementations
        Log(S_ERROR) << "Shader compliation failed! Info log:\n" << log.data();
    }
    // Mark shader for deletion (it won't be deleted now, as it's attached to the program)
    glDeleteShader(shader);
    return *this;
}

Shader& Shader::link()
{
    glLinkProgram(programId);
    GLint result = GL_FALSE;
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    if (result != GL_FALSE)
    {
        // Do nothing, I guess?
        Log(S_DEBUG) << "Shader program " << programId << " linked successfully";
    }
    else
    {
        GLint logLength;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength + 1);
        glGetProgramInfoLog(programId, logLength, &logLength, log.data());
        log[logLength] = '\0';
        Log(S_ERROR) << "Shader linkage failed! Info log:\n" << log.data();
    }
    return *this;
}

GLint Shader::attrLoc(const char* attrName)
{
    GLint result = glGetAttribLocation(programId, attrName);
    if (result < 0)
    {
        Log(S_WARNING) << "Attribute " << attrName << " is missing from program" << programId << "; optimized out?";
    }
    return result;
}

GLint Shader::unfLoc(const char* unfName)
{
    GLint result = glGetUniformLocation(programId, unfName);
    if (result < 0)
    {
        Log(S_WARNING) << "Uniform " << unfName << " is missing from program " << programId << "; optimized out?";
    }
    return result;
}

Shader& Shader::addStageFile(GLenum stage, const char* file)
{
    std::ifstream in(file);
    std::stringstream src;
    while (in.good())
    {
        std::string line;
        std::getline(in, line);
        src << line << "\n";
    }
    return addStage(stage, src.str().c_str());
}

}
