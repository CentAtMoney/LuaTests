#include "publisher.h"

void publisher::subscribe(subscriber* subscriber)
{
    subscribers_.push_front(subscriber);
}

void publisher::unsubscribe(subscriber* subscriber)
{
    subscribers_.remove(subscriber);
    subscriber->notify(unsubscribe_event);
}

void publisher::publish(const std::any& object)
{
    for(subscriber* subscriber : this->subscribers_)
    {
        subscriber->notify(object);
    }
}

publisher::~publisher()
{
    for(subscriber* subscriber : this->subscribers_)
    {
        if(subscriber != nullptr)
        {
            subscriber->notify(unsubscribe_event);
        }
    }
}