#include <screen.h>
const size_t scr_width = 80;
const size_t scr_height = 25;
unsigned short* screen = (unsigned short*)0xB8000;
static size_t scr_ptr = 0;
static size_t color = 0x2F;

void set_color(uint8_t background, uint8_t foreround)
{
	color = background<<4|foreround;
}

size_t get_color()
{
	return color;
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

void monitor_write(const char c)
{
	if(c=='\n')
	{
		scr_ptr = (scr_ptr-scr_ptr%scr_width)+scr_width;
	}
	else if(c=='\t')
	{
		int tab_count = 4;
		while(tab_count>0){
			monitor_write(' ');
			tab_count--;
		}
	}
	else if(c=='\b')
	{
		if(scr_ptr>0)
		{
			scr_ptr--;
			monitor_write(' ');
			scr_ptr--;
		}
	}
	else{
		screen[scr_ptr++] = (get_color())<<8 | c;
	}
	if(scr_ptr>=scr_width*scr_height){
		scr_ptr -= scr_width;
		scroll_down();
	}
}

unsigned short* get_screen_ptr()
{
	return screen;
}
size_t* screen_cursor_ptr()
{
	return &scr_ptr;
}