.set IRQ_BASE, 0x20

.section .text

.extern _ZN16InterruptManager15handleInterruptEhj
.global _ZN16InterruptManager22IgnoreInterruptRequestEv

# 名称格式是通过nm查看得到的
.macro HandleException num
.global _ZN16InterruptManager16HandlerException\num\()Ev
_ZN16InterruptManager16HandlerException\num\()Ev:
	movb $\num, (interruptnumber)
	jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN16InterruptManager26HandleInterruptRequest\num\()Ev:
	movb $\num + IRQ_BASE, (interruptnumber)
	jmp int_bottom
.endm

# 宏展开: 中断服务程序
# 	跳转到int_bottom
HandleInterruptRequest 0x00
HandleInterruptRequest 0x01



# jump target
# 中断处理函数
# 保存现场, 处理, 恢复现场
int_bottom:
	# 保存a寄存器
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	pushl %esp
	push (interruptnumber)
	# just jump to interrupt handler function: InterruptManager:handleInterrupt()
	call _ZN16InterruptManager15handleInterruptEhj
	# addl 
	movl %eax, %esp
	
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa

_ZN16InterruptManager22IgnoreInterruptRequestEv:

	iret

.data
	interruptnumber: .byte 0

	
