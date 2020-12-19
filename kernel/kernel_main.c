#include <screen.h>
#include <stdio.h>
#include <desc_table.h>
#include <timer.h>

int kmain(void *arg)
{
	set_color(2,15);
	init_gdt();
	init_idt();
	clear_screen();
	char *nikhil = "Nikhil Sharma\0";
	int p = printf("In the Beloved Memory of\n%s\n",nikhil);
	// asm volatile ("int $0x3");
	// asm volatile ("int $0x4");
	asm volatile("sti");
    
	init_timer(50);
	while(1);
	return 0;
}