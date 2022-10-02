# ch3 端口IO

我们的i386 OS会使用端口IO(port io)访问键盘。使用特殊的IN/OUT指令对某个地址的端口进行操作，使用cpp类对其进行封装。

- 对端口进行封装
	* 每个端口对象都是对某个port number读写的抽象
	* 可以使用虚函数以便统一管理
- port io使用专门的指令: IN/OUT
	* 内敛汇编inb/outb对一byte的操作
	* 内敛汇编inw/outw对一word(16bit)的操作


## result

- 面向对象
- 内敛汇编语法
- `-fno-stack-protector`编译参数

