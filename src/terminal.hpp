#pragma once
#include "g.hpp"
void draw_char(char c, uint16_t px, uint16_t py);
void draw_string(char *c, uint16_t px, uint16_t py);
int get_fwidth(char c);
int get_fheight(char c);