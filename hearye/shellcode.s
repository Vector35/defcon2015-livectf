.section .text, "ax"
.global _start
_start:
nop
mov x0,#0x490000
add x0, x0, #0x4000
add x0,x0,#0xA58
nop
#mov x0, #0x490000
#mov x1, #0x4A00
#add x0, x1, x0
#add x0, x1, #0x58

mov x1, #0x400000
add x1, x1, #0xea8
br x1
