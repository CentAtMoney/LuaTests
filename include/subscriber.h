#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "common.h"
#include "event.h"

class subscriber 
{
public:
    virtual ~subscriber() {}
    virtual void notify(const std::any& object) = 0;
    virtual void notify(std::shared_ptr<event> e);
};




#endif // SUBSCRIBER_H