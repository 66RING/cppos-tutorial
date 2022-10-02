// gdt类对gdt内存区域进行封装, 注意gdt内存布局要求
// 使用packed参数防止编译器优化对齐

#ifndef __GDT_H
#define __GDT_H
#include "types.h"

// GDT抽象, 内存地址相关, 用于设置gdtr寄存器
// 	gdtr寄存器格式和内部段描述符详见文档
class GlobalDescriptorTable {
	public:
		class SegmentDescriptor {
		private:
			uint16_t limit_lo;
			uint16_t base_lo;
			uint8_t base_hi;
			uint8_t type;
			uint8_t flags_limit_hi;
			uint8_t base_vhi;
		public:
			SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
			uint32_t Base();
			uint32_t Limit();
		} __attribute__((packed));

		SegmentDescriptor nullSegmentSelector;
		SegmentDescriptor unusedSegmentSelector;
		SegmentDescriptor codeSegmentSelector;
		SegmentDescriptor dataSegmentSelector;

	public:
		GlobalDescriptorTable();
		~GlobalDescriptorTable();

		uint16_t CodeSegmentSelector();
		uint16_t DataSegmentSelector();
};



#endif // !__GDT_H

