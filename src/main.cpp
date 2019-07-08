#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <iostream>

#include "gfx/Context.h"

#ifdef USE_EGL
# include "gfx/EGLContext.h"
#else
# include "gfx/SDLContext.h"
#endif

#include "util/logger.h"

int main()
{
    Log(S_DEBUG) << "Program start";
    #ifdef USE_EGL
    Gfx::EglContext ctx;
    #else
    Gfx::SDLContext ctx{1280, 720};
    #endif
    Log(S_DEBUG) << "Context created";
    
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
