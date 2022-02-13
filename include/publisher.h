#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "subscriber.h"

#include <forward_list>
#include <any>

// event sent to subscriber upon publisher destruction and or
// subscriber unsubscription
struct unsubscribe_event {} unsubscribe_event;

class publisher
{
public:
    void subscribe(subscriber* subscriber);

    void unsubscribe(subscriber* subsriber);

    void publish(const std::any& object);

    ~publisher();

private:
    std::forward_list<subscriber*> subscribers_;

};


#endif // PUBLISHER_H