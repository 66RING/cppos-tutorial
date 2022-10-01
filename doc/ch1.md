# ch1

- kernel.cpp
- linker.ld
- loader.s
- type.h

- 指定链接脚本链接目标文件
	* ld -T
	* 在对应段中把符号暴露出来
- loader
	* 使用`grub-mkrescue`构建简易loader
	* 汇编代码中需要一个元数据段`multiboot`供grub识别
	* bootloader加载汇编代码执行, 最小化实现是
		+ 汇编中定义栈段, sp置为该栈然后跳转到主函数
- 不使用任何库, 直接对硬件操作实现简单打印
	* 显存在`0xb8000`处, 是一byte的颜色一byte的char这么的格式
	* 所以简单`print`实现可以是直接对这段地址写入
	* 使用`extern`暴露出主函数使能从汇编代码中跳转

