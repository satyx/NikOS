#include <screen.h>
#include <stdio.h>
#include <gdt.h>

int kmain(void *arg)
{
	set_color(2,15);
	init_gdt();
	clear_screen();
	char *nikhil = "Nikhil Sharma\0";
	int p = printf("In the Beloved Memory of\n%s\n",nikhil);
	while(1);
	return 0;
}