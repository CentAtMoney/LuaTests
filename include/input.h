#ifndef INPUT_H
#define INPUT_H


struct key_event
{
    int key;
    int scancode;
    int mods;
}

struct key_press_event : public key_event
{
};

struct key_release_event : public key_event
{
};

struct key_repeat_event : public key_event
{
};

struct cursor_move_event
{
    double x;
    double y;
};

struct mouse_scroll_event
{
    double x;
    double y;
};




#endif