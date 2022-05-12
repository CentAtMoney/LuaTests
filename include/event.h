#ifndef EVENT_H
#define EVENT_H


class event
{
public:
    virtual void handle() = 0;

    bool is_handled() const;

protected:
    bool handled_;
};



#endif