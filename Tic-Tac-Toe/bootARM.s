    .equ FLAGS, 0
    .equ MAGIC, 0x1BADB002

    .global _start
    .section .multiboot

    .word MAGIC
    .word FLAGS
    .word - (MAGIC + FLAGS)

stackBottom:
    .space 4096  @ Allocate 4096 bytes for the stack

stackTop:

    .section .text
    .global _start
    _start:
        ldr sp, =stackTop  @ Set stack pointer to stackTop

        bl kernel_entry    @ Call kernel_entry function

        cpsid i            @ Disable interrupts

    hltLoop:
        wfi                @ Wait for interrupt (halt in ARM)
        b hltLoop          @ Infinite loop

    .size _start, . - _start
