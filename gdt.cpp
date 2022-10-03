#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
	: nullSegmentSelector(0, 0, 0),
	unusedSegmentSelector(0, 0, 0),
	codeSegmentSelector(0, 64*1024*1024, 0x9A),
	dataSegmentSelector(0, 64*1024*1024, 0x92) 
{
	// gdtr寄存器设置: 基地址(47~16), 界限(15~0)
	// 编译器对数组内存的布局问题, 32位编译器将数组的低索引放在了高地址(栈)
	uint32_t i[2];
	i[0] = sizeof(GlobalDescriptorTable) << 16;
	i[1] = (uint32_t)this;

	// 数组地址与编译器相关, i[]作为临时数组
	asm volatile (
			"lgdt (%0)"
			:
			:"p" (((uint8_t *)i)+2));
}


GlobalDescriptorTable::~GlobalDescriptorTable(){}


uint16_t GlobalDescriptorTable::DataSegmentSelector() {
	return (uint8_t*)&dataSegmentSelector - (uint8_t*) this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector() {
	return (uint8_t*)&codeSegmentSelector - (uint8_t*) this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags) {
	uint8_t* target = (uint8_t*)this;
	
	if(limit <= 65535) {
		target[6] = 0x40;
	} else {
		if((limit & 0xFFF) != 0xFFF) 
			limit = (limit >> 12) -1;
		else 
			limit = limit >> 12;

		target[6] = 0xC0;
	}

	// 15~0处的limit bit
	target[0] = limit & 0xFF;
	target[1] = (limit >> 8) & 0xFF;
	// + 51~48出的limit bit
	target[6] |= (limit >> 16) & 0xF;

	// 31~16处的base bit
	target[2] = base & 0xFF;
	target[3] = (base >> 8) & 0xFF;
	// + 39~32处的base bit
	target[4] = (base >> 16) & 0xFF;
	// + 63~56处的base bit
	target[7] = (base >> 24) & 0xFF;

	// 55~52处的flags bit
	target[5] = flags;

}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base() {
	uint8_t* target = (uint8_t*)this;
	uint32_t result = target[7];
	result = (result << 8) + target[4];
	result = (result << 8) + target[3];
	result = (result << 8) + target[2];
	return result;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit() {
	uint8_t* target = (uint8_t*)this;
	uint32_t result = target[6] & 0xF;
	result = (result << 8) + target[1];
	result = (result << 8) + target[0];

	if((target[6] & 0xC0) == 0xC0)
		result = (result << 12) | 0xFFF;

	return result;
}

