#include "publisher.h"


publisher::publisher()
{
}

publisher::publisher(std::vector<subscriber*> subscribers)
{
    for(subscriber* subscriber: subscribers)
    {
        this->subscribe(subscriber);
    }
}

void publisher::subscribe(subscriber* subscriber)
{
    subscribers_.push_front(subscriber);
}

void publisher::unsubscribe(subscriber* subscriber)
{
    unsubscribe_event e;
    subscribers_.remove(subscriber);
    subscriber->notify(e);
}

void publisher::publish(const std::any& object)
{
    for(subscriber* subscriber : this->subscribers_)
    {
        subscriber->notify(object);
    }
}

void publisher::publish(std::shared_ptr<event> e)
{
    for(subscriber* subscriber : this->subscribers_)
    {
        subscriber->notify(e);
    }
}

publisher::~publisher()
{
    unsubscribe_event e;
    for(subscriber* subscriber : this->subscribers_)
    {
        if(subscriber != nullptr)
        {
            subscriber->notify(e);
        }
    }
}