#pragma once

#include <memory>
#include <functional>

namespace Gfx
{

using EventPtr = void*;

/* Generic context interface */
class Context
{
public:
    virtual ~Context() {};
    /** Swap buffers - show rendered data on the screen */
    virtual void swap() = 0;
    /** Make the context "current" */
    virtual bool makeCurrent() = 0;
    virtual uint32_t getWidth() = 0;
    virtual uint32_t getHeight() = 0;

    virtual void setEventCallback(std::function<void(EventPtr)> &callback) = 0;
};

}
