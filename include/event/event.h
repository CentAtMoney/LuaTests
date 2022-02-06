#ifndef EVENT_EVENT_H
#define EVENT_EVENT_H

#include <typeinfo>

class event
{
public:
    virtual const std::type_info& get_type() const;
};

class event_callback
{
public:
    virtual const std::type_info& get_type() const = 0;
    virtual void operator()(const event* event) = 0;
};


#endif