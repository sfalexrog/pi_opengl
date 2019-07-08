#pragma once

#include "Context.h"
#include <memory>

namespace Gfx
{

class SDLContext : public Context
{
private:
    struct ContextData;
    std::unique_ptr<ContextData> data;

public:
    SDLContext(uint32_t width, uint32_t height);
    ~SDLContext() final;
    /** Swap buffers - show rendered data on the screen */
    void swap() final;
    /** Make the context "current" */
    bool makeCurrent() final;
    uint32_t getWidth() final;
    uint32_t getHeight() final;

    void setEventCallback(std::function<void(EventPtr)> &cb) final;
};

}
