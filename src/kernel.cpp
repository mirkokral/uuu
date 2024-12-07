#include <stdbool.h>
#include <stddef.h>
#include "g.hpp"
#include "include/multiboot.h"
#include "include/colors.h"
#include "errors.hpp"
#include "video.hpp"
#include "logger.hpp"
#include "terminal.hpp"
#include "mem.hpp"

bool show_mbh_info(struct multiboot_info *mbh, char *name, int offset)
{
	// kernel_log("Showing mbh info: ");
	// kernel_log(name);
	// kernel_log("\n");

	kernel_log(name);
	kernel_log(": ");
	bool rv = false;
	if (mbh->flags & (1 << offset))
	{
		rv = true;
		kernel_log("Yes");
	}
	else
	{
		kernel_log("No");
	}
	kernel_log("\n");
	return rv;
}

void lock() {
	while(true){}
}

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

extern "C"
{

	void kernel_main(struct multiboot_info *mbh, uint32_t mb_mag)
	{
		// ((uint32_t*)((vbe_info_structure*)mbh->vbe_mode_info)->framebuffer)[2000] = 0xFFFFFFFF;
		kernel_log("Hi!\n");

		show_mbh_info(mbh, "Mem limits   ", 12);
		show_mbh_info(mbh, "Boot dev     ", 11);
		show_mbh_info(mbh, "Cmdline      ", 10);
		show_mbh_info(mbh, "Mods         ", 9);
		show_mbh_info(mbh, "Syms 1       ", 8);
		show_mbh_info(mbh, "Syms 2       ", 7);
		show_mbh_info(mbh, "Memory map   ", 6);
		show_mbh_info(mbh, "Drive list   ", 5);
		show_mbh_info(mbh, "Config table ", 4);
		show_mbh_info(mbh, "BL name      ", 3);
		show_mbh_info(mbh, "APM table    ", 2);
		show_mbh_info(mbh, "Vesa         ", 1);
		show_mbh_info(mbh, "Framebuffer  ", 0);

		kernel_log("Init video\n");
		
		Video::Init(mbh);
		

		mem_init(mbh->mem_upper, mbh->mem_lower);

		
		
		
		int calcr[Video::width];
		int calcg[Video::width];
		int calcb[Video::width];
		for(uint32_t n = 0; n < Video::width; n++) {
			float r;
			float g;
			float b;
			float h = ((float)n)/Video::height*365.0f;
			float s = 1;
			float v = 1;
			HSVtoRGB(r, g, b, h, s, v);
			// Video::SetPixel(n, i, (int)(r*255), (int)(g*255), (int)(b*255));
			calcr[n] = (int)(r*255);
			calcg[n] = (int)(g*255);
			calcb[n] = (int)(b*255);

		}
		
		for(uint32_t i = 0; i < Video::height; i++) {
			for(uint32_t n = 0; n < Video::width; n++) {
				Video::SetPixel(n, i, calcr[n], calcg[n], calcb[n]);

			}

		}
		draw_string("Hello\nmultiline world!", 10, 10);
		draw_string("We graphics and text!!", 10, 80);
		draw_string(kernel_logbuf, 10, 100);
		// kernel_log("MB width: ");

		// citoa(mbh->vbe_mode_info, buf, 10);
		// kernel_log(buf);
		// kernel_log("\n");
	}

	void kernel_end(void)
	{
		kernel_panic("Kernel ended.");
		while (true)
		{
		}
	}
}