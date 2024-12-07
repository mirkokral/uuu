#include "errors.hpp"
#include "include/serial.h"
#include "video.hpp"
#include "terminal.hpp"

void kernel_panic(char *issue)
{
    serial_write_string("Kernel panic\n");
    serial_write_string("Issue: ");
    serial_write_string(issue);
    serial_write_string("\n");

    if (Video::inited)
    {
        
        draw_string("Kernel panic", 0, 0);
        draw_string("Issue: ", 0, get_fheight('I'));
        draw_string(issue, get_fwidth('I')*7, get_fheight('I'));
    }
    while (true)
    {
        asm("hlt");
    }
}