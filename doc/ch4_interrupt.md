# ch4 interrupt

- interrupt.cpp
- interruptstubs.s

![](https://images2015.cnblogs.com/blog/591443/201704/591443-20170411145524610-601268965.jpg)

![](https://image-static.segmentfault.com/325/620/3256205223-5914c777043ff_articlex)

- 类似gdt, 中断描述符表(idt)同样由table本体(若干interrupt gate)和table地址需要设置
	* idt中有多种类型的gate, 内存布局如上图所示
	* 由`lidt`指令设置idtr寄存器告知位置, idtr寄存器内存布局如上图
	* 使用`sti`指令启动中断
- 硬编码汇编完成中断服务例程
	* 使用`nm file.o`查看编译后的函数名称
	* 使用汇编宏批量生成处理程序
- 使用PIO对中断控制器进行控制


## Result

- idt, gate, idtr格式
- 汇编代码宏
- 微机原理: 使用PIO对PIC进行控制
	* TODO:
