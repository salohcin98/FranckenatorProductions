    .equ FLAGS, 0
    .equ MAGIC, 0x1BADB002
    .global _start
    .section .multiboot
    .word MAGIC
    .word FLAGS
    .word - (MAGIC + FLAGS)

stackBottom:
    .space 4096  

stackTop:

    .section .text
    .global _start
    _start:
        ldr sp, =stackTop  

        bl kernel_entry   

        cpsid i            

    hltLoop:
        wfi              
        b hltLoop          

    .size _start, . - _start
