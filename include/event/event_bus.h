#ifndef EVENT_EVENT_BUS_H
#define EVENT_EVENT_BUS_H
#include "event/event.h"

#include <map>
#include <vector>
#include <typeinfo>
#include <typeindex>


class event_bus
{
public:
    event_bus();
    void register_type(const std::type_info& type, const std::type_info& parent);
    void subscribe(event_callback* callback);
    void unsubscribe(event_callback* callback);
    void publish(const event* event); 

protected:

    void call_callbacks(const std::type_index, const event* event);

    // maps parent type to child type starting with root as event
    std::map<std::type_index, std::vector<std::type_index>> type_registry_;

    // maps callback to type it's specified to work on
    // will be called if parent types are published due to type_registry_
    std::map<std::type_index, std::vector<event_callback*>> callbacks_;


};

#endif