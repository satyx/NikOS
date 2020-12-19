/* gdt */
.global gdt_flush

gdt_flush:
   mov 4(%esp),%eax  //; Get the pointer to the GDT, passed as a parameter.
   lgdt (%eax)        //; Load the new GDT pointer

   mov $0x10, %ax      //; 0x10 is the offset in the GDT to our data segment
   mov %ax, %ds        //; Load all data segment selectors
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs
   mov %ax, %ss
   jmp $0x08,$flush
flush:
   ret

.global idt_flush    //; Allows the C code to call idt_flush().

idt_flush:
   mov 4(%esp),%eax  //; Get the pointer to the IDT, passed as a parameter.
   lidt (%eax)        //; Load the IDT pointer.
   ret
