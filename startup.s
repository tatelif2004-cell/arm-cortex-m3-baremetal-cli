.syntax unified
    .cpu cortex-m3
    .thumb

    .global vtable
    .global reset_handler

    .section .vectors, "a"
vtable:
    .word _stack_top        
    .word reset_handler     
    .section .text
    .type reset_handler, %function
reset_handler:
    
    ldr r0, =_etext         
    ldr r1, =_sdata         
    ldr r2, =_edata         

copy_data_loop:
    cmp r1, r2            
    bge zero_bss_init      
    ldr r3, [r0], #4        
    str r3, [r1], #4        
    b copy_data_loop

zero_bss_init:
    
    ldr r1, =_sbss
    ldr r2, =_ebss
    movs r3, #0

zero_bss_loop:
    cmp r1, r2
    bge call_main
    str r3, [r1], #4        
    b zero_bss_loop

call_main:

    bl main

hang:
    b hang                  