#include "event/event_bus.h"
#include <stdexcept>

event_bus::event_bus()
{
    type_registry_[std::type_index(typeid(event))] = {};
}

void event_bus::register_type(const std::type_info& type, const std::type_info& parent)
{
    // may have to initialize vector idk
    // I did it in the constructor since we need to have the event type at the root of the tree
    // maybe that's not how it should be done TEST IT
    type_registry_[std::type_index(parent)].push_back(type);
}

void event_bus::subscribe(event_callback* callback)
{
    const std::type_index index(callback->get_type());

    // we do this since unsubscribing possibly leaves a nullptr in the middle of the callback vector
    // this shouldn't need to be fast 
    for(int i = 0; i < callbacks_[index].size(); i++)
    {
        if(callbacks_[index][i] == nullptr)
        {
            callbacks_[index][i] = callback;
        }
    }
    callbacks_[index].push_back(callback);
}

void event_bus::unsubscribe(event_callback* callback)
{
    const std::type_index index(callback->get_type());

    for(int i = 0; i < callbacks_[index].size(); i++) 
    {
            if(callbacks_[index][i] == callback)
            {
                // no delete since we don't handle allocation and deallocation of callback
                // that's the job of whoever gave us the pointer
                // maybe we should use shared pointers
                callbacks_[index][i] = nullptr;
            }
    }
    throw std::invalid_argument("Callback is not subscribed.");
}

void event_bus::publish(const event* event)
{
    const std::type_index index(event->get_type());

    std::vector<std::type_index> to_call = type_registry_[index];

    // to perserve order in the type heirarchy we call this one first
    call_callbacks(index, event);

    for(int i = 0; i < to_call.size(); i++)
    {
        call_callbacks(to_call[i], event);
    }

}

void event_bus::call_callbacks(const std::type_index index, const event* event)
{
    for(int i = 0; i < callbacks_[index].size(); i++)
    {
        // definitely an ugly line of code
        // I don't even know if it works :P
        (*callbacks_[index][i])(event);
    }
}