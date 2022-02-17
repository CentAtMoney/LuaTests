// main.cpp
#include "application.h"


int main(int argc, char** argv)
{

    application::create_info application_create_info;
    application_create_info.window_create_info = {
        .title = "LuaTest",
        .width = 800,
        .height = 600,
    };


    application app(application_create_info);
    app.run();
    return 0;

}