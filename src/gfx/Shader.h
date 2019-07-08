#pragma once

#include <GLES2/gl2.h>

namespace Gfx
{

class Shader
{
private:

public:
    Shader();
    ~Shader();

    Shader& addStage(GLenum stage, const char* source);
    Shader& link();
    

};

}
