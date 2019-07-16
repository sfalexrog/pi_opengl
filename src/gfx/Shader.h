#pragma once

#include <GLES2/gl2.h>

namespace Gfx
{

class Shader
{
private:
    GLuint programId;

public:
    Shader();
    ~Shader();

    Shader& addStage(GLenum stage, const char* source);
    Shader& link();

    Shader& use() { glUseProgram(programId); };

    GLint attrLoc(const char* attrName);
    GLint unfLoc(const char* unfName);

    Shader& addStageFile(GLenum stage, const char* file);
};

}
