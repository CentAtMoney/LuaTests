#ifndef RENDERER_H
#define RENDERER_H
#include "subscriber.h"

class renderer : public subscriber
{
public:
    void notify(const std::any& object) override;

    void render();

private:
};

#endif