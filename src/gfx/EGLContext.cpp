#include "EGLContext.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <bcm_host.h>
#include <interface/mmal/mmal.h>

namespace Gfx
{

struct EglContext::ContextData
{
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

    uint32_t screenWidth;
    uint32_t screenHeight;

    EGL_DISPMANX_WINDOW_T nativeWindow;

    DISPMANX_ELEMENT_HANDLE_T dispmanElement;
    DISPMANX_DISPLAY_HANDLE_T dispmanDisplay;
    DISPMANX_UPDATE_HANDLE_T dispmanUpdate;

    VC_RECT_T dstRect;
    VC_RECT_T srcRect;
};


// Default attributes for context - should be more or less fine for our purposes
const EGLint GAttribList[] = {
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_DEPTH_SIZE, 16,
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_NONE
};

const EGLint GCtxAttribList[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

EglContext::EglContext() : data(new EglContext::ContextData)
{
    // Initialize broadcom host
    bcm_host_init();

    // Usual EGL initialization dance follows

    // Get default EGL display
    data->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(EGL_NO_DISPLAY != data->display);

    // Initialize EGL library; we don't care about the version
    EGLBoolean result = eglInitialize(data->display, NULL, NULL);
    assert(EGL_FALSE != result);

    EGLConfig config;
    EGLint num_config;
    // Choose the first suitable config
    result = eglChooseConfig(data->display, GAttribList, &config, 1, &num_config);
    assert(EGL_FALSE != result);

    // Set the context as an OpenGL ES config
    result = eglBindAPI(EGL_OPENGL_ES_API);
    assert(EGL_FALSE != result);

    // Create actual context handle
    data->context = eglCreateContext(data->display, config, EGL_NO_CONTEXT, GCtxAttribList);
    assert(EGL_FALSE != result);

    int32_t success = graphics_get_display_size(0, &data->screenWidth, &data->screenHeight);
    assert(0 <= success);

    data->dstRect.x = 0;
    data->dstRect.y = 0;
    data->dstRect.width = data->screenWidth;
    data->dstRect.height = data->screenHeight;

    data->srcRect.x = 0;
    data->srcRect.y = 0;
    // Source rect width and height is a 16.16 fixed point value,
    // so we transform it accordingly
    data->srcRect.width = data->dstRect.width << 16;
    data->srcRect.height = data->dstRect.height << 16;

    // Establish dispmanx connection
    // Device 0 is our LCD (HDMI?)
    data->dispmanDisplay = vc_dispmanx_display_open(0);
    data->dispmanUpdate = vc_dispmanx_update_start(0);

    data->dispmanElement = vc_dispmanx_element_add(
        data->dispmanUpdate,
        data->dispmanDisplay,
        /* layer */ 0,
        &data->dstRect,
        /* src */ 0,
        &data->srcRect,
        DISPMANX_PROTECTION_NONE,
        /* alpha */ NULL,
        /* clamp */ NULL,
        DISPMANX_TRANSFORM_T::DISPMANX_NO_ROTATE);

    data->nativeWindow.element = data->dispmanElement;
    data->nativeWindow.width = data->screenWidth;
    data->nativeWindow.height = data->screenHeight;

    // Send updated data about our window to dispman
    vc_dispmanx_update_submit_sync(data->dispmanUpdate);

    // Create our window surface (backed by dispman)
    data->surface = eglCreateWindowSurface(
        data->display,
        config,
        &data->nativeWindow,
        /* attrib_list */ NULL);
    assert(EGL_NO_SURFACE != data->surface);

    // Finally, make our context current
    assert(false != makeCurrent());
}

bool EglContext::makeCurrent()
{
    return EGL_FALSE != eglMakeCurrent(
        data->display,
        data->surface,
        data->surface,
        data->context);
}

EglContext::~EglContext()
{
    // TODO: free all resources
}

void EglContext::swap()
{
    eglSwapBuffers(data->display, data->surface);
}

uint32_t EglContext::getHeight()
{
    return data->screenHeight;
}

uint32_t EglContext::getWidth()
{
    return data->screenWidth;
}

void EglContext::setEventCallback(std::function<void(EventPtr)> &cb)
{
    throw std::bad_exception();
}

}
