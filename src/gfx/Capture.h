#pragma once

#include <GLES2/gl2.h>

namespace Gfx
{

class Capture
{
public:
    virtual ~Capture() {}

    virtual bool canCaptureRGBA() = 0;
    virtual bool canCaptureYUV() = 0;
    virtual void getRGBAFrame() = 0;
    virtual void getYUVFrame() = 0;
};

}
