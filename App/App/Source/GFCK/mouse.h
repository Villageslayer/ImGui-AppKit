#pragma once
#include <winternl.h>


class Mouse {
public:
    Mouse();
    ~Mouse();
    bool open();
    bool close();
    void move(char button, char x, char y, char wheel);

private:
    struct MOUSE_IO {
        char button;
        char x;
        char y;
        char wheel;
        char unk1;
    };

    HANDLE g_input;
    IO_STATUS_BLOCK g_io;
    BOOL g_found_mouse;

    bool callmouse(MOUSE_IO* buffer);
    NTSTATUS device_initialize(PCWSTR device_name);
};
