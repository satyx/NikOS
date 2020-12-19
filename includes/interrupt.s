/*interrupts*/
.macro ISR_NOERRCODE p  //; define a macro, taking one parameter
  .global isr\p
  isr\p:
    cli
    push $0
    push $\p
    jmp isr_common_stub
.endm
.macro ISR_ERRCODE q  //; define a macro, taking one parameter
  .global isr\q
  isr\q:
    cli
    push $\q
    jmp isr_common_stub
.endm


ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

.extern isr_handler
isr_common_stub:
  pusha                    

  mov %ds, %ax             
  push %eax                

  mov $0x10, %ax  
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  push %esp
  call isr_handler

  pop %ebx
  pop %ebx        
  mov %bx, %ds
  mov %bx, %es
  mov %bx, %fs
  mov %bx, %gs

  popa           
  add $8, %esp
  sti
  iret