#include "Context.h"

#include <memory>

namespace Gfx
{

class EglContext : public Context
{
private:
    struct ContextData;
    std::unique_ptr<ContextData> data;

public:
    EglContext();
    ~EglContext() final;

    void swap() final;

    bool makeCurrent() final;
    uint32_t getWidth() final;
    uint32_t getHeight() final;

    /** Event callbacks are not supported for EGL contexts, but
     * the function is there for compatibility
     */
    void setEventCallback(std::function<void(EventPtr)> &cb) final;
};

}
