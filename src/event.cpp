// event.h

#include "event.h"

bool event::is_handled() const
{
    return this->handled_;
}