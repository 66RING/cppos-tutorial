# ch2

- gdt.cpp
- kernel.cpp


这节涉及x86硬件(gdt)细节

![](https://i.stack.imgur.com/OANZQ.png)

gdt身为一个table由若干段描述符组成, 这里用`SegmentDescriptor`类封装，段描述符内存布局要求如上图。

- 保护模式下内存的访问 = 段选择子(描述符索引) + offet
- 我们这里使用cpp class对其进行封装, 因此特别需要注意内存布局问题
	* 用到编译器参数`__attribute__((packed))`, 取消对对齐的优化, 所见即所得
- 段描述符初始化
	* 字段根据x86 gdt手册排列好后, 构造函数就是对这些字段进行赋值
	* 如上内存布局所示, flag bit用于告知是什么段
- gdt初始化
	* GlobalDescriptorTable类是整个table的抽象, 由若干描述符
	* 构造函数需要内敛汇编使用`lgdt`设置gdtr寄存器告知table地址
	* gdtr寄存器内存布局有求: 基地址(47~16), 界限(15~0)
		+ 需要注意这里的一个细节: 编译器对函数体内数组内存地址分配问题, 数组索引0可能在高地址, 数组索引1可能在低地址, 这些的编译器相关的可以使用预编译宏处理
- 使用`lgdt`指令保存gdt地址到gdt寄存器(gdtr)
	* 使用c语言内敛汇编`asm`


## result

- 段描述符
- gdt
- 编译器细节
	* 函数中的数组的内存布局
	* 类的内存布局
	* 编译器参数`packed`
