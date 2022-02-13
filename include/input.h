#ifndef INPUT_H
#define INPUT_H

struct key_press_event
{
    int key;
    int scancode;
    int mods;
};

struct key_release_event
{
    int key;
    int scancode;
    int mods;
};

struct key_repeat_event
{
    int key;
    int scancode;
    int mods;
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

struct mouse_button_press_event
{
    int button;
    int mods;
};

struct mouse_button_release_event
{
    int button;
    int mods;
};



#endif