#include "video.hpp"

uint32_t* Video::framebuffer;
uint16_t  Video::width;
uint16_t  Video::height;
bool      Video::inited      = false;

void Video::Init(multiboot_info *mbha)
{
    if(mbha->flags & (1<<1) == 0) {
        inited=false;
        return;
    }
    auto vbeinfo = (vbe_info_structure*)mbha->vbe_mode_info;
    Video::framebuffer = (uint32_t*)vbeinfo->framebuffer;
    Video::width = vbeinfo->width;
    Video::height = vbeinfo->height;
    inited=true;
}
