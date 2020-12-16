#include "screen.h"

const size_t scr_width = 80;
const size_t scr_height = 25;
unsigned short* screen = (unsigned short*)0xB8000;
static size_t scr_ptr = 0;
static size_t color = 0x2F;

void set_color(uint8_t background, uint8_t foreround)
{
	color = background<<4|foreround;
}

void clear_screen()
{
	uint8_t row_ptr,column_ptr;
	for(row_ptr=0;row_ptr<scr_height;row_ptr++)
	{
		for(column_ptr=0;column_ptr<scr_width;column_ptr++)
		{
			screen[row_ptr*scr_width+column_ptr] = color<<8|0x20;
		}
	}
	scr_ptr = 0;
}

void clear_row(uint8_t row_ptr)
{
	uint8_t column_ptr = 0;
	for(;column_ptr<scr_width;column_ptr++)
		screen[row_ptr*scr_width+column_ptr] = color<<8|0x20;
}

void scroll_down()
{
	uint8_t row_ptr,column_ptr;
	for(row_ptr=0;row_ptr<scr_height-1;row_ptr++)
	{
		for(column_ptr=0;column_ptr<scr_width;column_ptr++)
		{
			screen[row_ptr*scr_width+column_ptr] = screen[(row_ptr+1)*scr_width+column_ptr];
		}
	}
	clear_row(scr_height-1);
}