// subscriber.cpp

#include "subscriber.h"


void subscriber::notify(std::shared_ptr<event> e)
{
    if(!e->is_handled())
    {
        e->handle();
    }
}
