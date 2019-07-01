#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <iostream>

#include "gfx/Context.h"

int main()
{
    Gfx::Context ctx;
    std::cout << "Screen started" << std::endl;
    
    float r = 0.0f;
    while(1)
    {
        r += 0.01f;
        if (r > 1.0f) {r = 0.0f;}
        
        glClearColor(r, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ctx.swap();
    }
}