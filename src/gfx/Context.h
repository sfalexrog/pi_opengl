#pragma once

#include <memory>

namespace Gfx
{

struct ContextData;

class Context
{
private:
    std::unique_ptr<ContextData> data;

public:
    Context();
    ~Context();
    /** Swap buffers - show rendered data on the screen */
    void swap();
    /** Make the context "current" */
    bool makeCurrent();
    uint32_t getWidth();
    uint32_t getHeight();
};

}
