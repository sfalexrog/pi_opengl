#include "SDLContext.h"

#include "util/logger.h"

#include <SDL.h>

namespace Gfx
{

namespace /* anonymous */
{
    void nullCallback(EventPtr ev)
    {
        SDL_Event* sev = static_cast<SDL_Event*>(ev);
        if (sev->type == SDL_QUIT)
        {
            LogAssert(false);
        }
        return;
    }
}

struct SDLContext::ContextData
{
    std::function<void(EventPtr)> eventCallback;

    uint32_t screenWidth;
    uint32_t screenHeight;

    SDL_Window *win;
    SDL_GLContext ctx;
};

SDLContext::SDLContext(uint32_t width, uint32_t height) : data(new SDLContext::ContextData)
{
    data->eventCallback = nullCallback;

    data->screenWidth = width;
    data->screenHeight = height;

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    data->win = SDL_CreateWindow("pi_opengl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 width, height, SDL_WINDOW_OPENGL);
    LogAssert(nullptr != data->win);

    data->ctx = SDL_GL_CreateContext(data->win);
    LogAssert(nullptr != data->ctx);

    int result = SDL_GL_MakeCurrent(data->win, data->ctx);
    LogAssert(0 == result);
}

SDLContext::~SDLContext()
{
    SDL_GL_DeleteContext(data->ctx);
    SDL_DestroyWindow(data->win);
}

void SDLContext::swap()
{
    SDL_Event ev;
    while(SDL_PollEvent(&ev))
    {
        data->eventCallback(&ev);
    }
    SDL_GL_SwapWindow(data->win);
}

uint32_t SDLContext::getWidth()
{
    return data->screenWidth;
}

uint32_t SDLContext::getHeight()
{
    return data->screenHeight;
}

bool SDLContext::makeCurrent()
{
    return SDL_GL_MakeCurrent(data->win, data->ctx) == 0;
}

void SDLContext::setEventCallback(std::function<void(EventPtr)> &cb)
{
    data->eventCallback = cb;
}

}
