#include <screen.h>
#include <stdio.h>
int kmain(void *arg)
{
	set_color(2,15);
	clear_screen();
	char *nikhil = "Nikhil Sharma\0";
	int p = printf("In the Beloved Memory of\n%s\n",nikhil);
	while(1);
	return 0;
}