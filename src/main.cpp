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
#include "gfx/Shader.h"

#include <unistd.h>

int main()
{
    Log(S_DEBUG) << "Program start";
    {
        char *workdir = getcwd(nullptr, 0);
        Log(S_DEBUG) << "Working directory is: " << workdir;
        free(workdir);
    }
    #ifdef USE_EGL
    Gfx::EglContext ctx;
    #else
    Gfx::SDLContext ctx{1280, 720};
    #endif
    Log(S_DEBUG) << "Context created";

    Gfx::Shader passthrough;
    passthrough.addStageFile(GL_VERTEX_SHADER, "data/vertex_passthrough.vert")
        .addStageFile(GL_FRAGMENT_SHADER, "data/fragment_passthrough.frag")
        .link();

    Log(S_DEBUG) << "Shaders loaded";

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
