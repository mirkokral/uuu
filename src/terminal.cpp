#include "terminal.hpp"
#include "include/font.h"
#include "video.hpp"

void draw_char(char c, uint16_t px, uint16_t py)
{
	if(c >= 128) return;
	uint16_t coffset = ((uint16_t)font_height * font_width);
	uint16_t boffset = coffset * (uint16_t)c;
	for (int y = 0; y < font_height; y++)
	{
		for (int x = 0; x < font_width; x++)
		{
			// could do this with memcpy but dont have that implemented at the time of this
			Video::SetPixel(px + x, py + y,
							font[boffset + (y * font_width) + x] ? 255 : 0,
							font[boffset + (y * font_width) + x] ? 255 : 0,
							font[boffset + (y * font_width) + x] ? 255 : 0);
		}
	}
}

void draw_string(char *c, uint16_t px, uint16_t py)
{
	int posx = 0;
	int posy = 0;
	for (int pos = 0; pos < strlen(c); pos++)
	{
		if (c[pos] == '\n')
		{
			posx = 0;
			posy++;
		}
		else
		{
			draw_char(c[pos], px + posx * font_width, py + posy * font_height);
			posx++;
		}
	}
}

int get_fwidth(char c)
{
    return font_width;
}

int get_fheight(char c)
{
    return font_height;
}
