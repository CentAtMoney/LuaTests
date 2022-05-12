#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "subscriber.h"
#include "common.h"

// event sent to subscriber upon publisher destruction and or
// subscriber unsubscription
struct unsubscribe_event
{
};

class publisher
{
public:
    
    publisher();

    publisher(std::vector<subscriber*> subscribers);

    virtual void subscribe(subscriber* subscriber);

    virtual void unsubscribe(subscriber* subscriber);

    virtual void publish(const std::any& object);

    virtual void publish(std::shared_ptr<event> e);

    ~publisher();

private:
    std::forward_list<subscriber*> subscribers_;

};


#endif // PUBLISHER_H