#include <screen.h>
#include <stdio.h>
#include <desc_table.h>
#include <timer.h>
#include <keyboard.h>
int kmain(void *arg)
{
	set_color(2,15);
	clear_screen();
	char *nikhil = "Nikhil Sharma\0";
	int p = printf("                            In the Beloved Memory of\n                                 %s\n\n",nikhil);
	
	init_gdt();
	printf("Global Descriptor Table Initialised Successfully....\n");
	init_idt();
	printf("Programmable Interrupt Controller remapped Successfully...\n");
	printf("Interrupt Descriptor Table Initialised Successfully....\n");
	// asm volatile ("int $0x3");
	// asm volatile ("int $0x4");
	init_keyboard();
	printf("Programmable Interval Timer Initialised Successfully...\n");
	printf("Keyboard Initialised Successfully...\n");

	asm volatile("sti");
    
	//init_timer(50);
	while(1);
	return 0;
}