#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "subscriber.h"

#include <forward_list>
#include <any>
#include <vector>

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

    virtual void unsubscribe(subscriber* subsriber);

    virtual void publish(const std::any& object);

    ~publisher();

private:
    std::forward_list<subscriber*> subscribers_;

};


#endif // PUBLISHER_H