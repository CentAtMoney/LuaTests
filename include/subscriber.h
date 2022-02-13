#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <any>

class subscriber 
{
public:
    virtual void notify(const std::any& object) = 0;
};




#endif // SUBSCRIBER_H
