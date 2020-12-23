#ifndef SCREEN_H
#define SCREEN_H

#include <basics.h>

#define SCR_WIDTH 80
#define SCR_HEIGHT 25
#define TAB_LENGTH 4
void set_color(uint8_t, uint8_t);
size_t get_color();
void clear_screen();
void clear_row(uint8_t);
void scroll_down();
void monitor_write(const char);
unsigned short* get_screen_ptr();
size_t* screen_cursor_ptr();

#endif