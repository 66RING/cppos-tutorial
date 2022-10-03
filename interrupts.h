#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include"types.h"
#include"port.h"
#include"gdt.h"


class InterruptManager {
protected:
	// Interrupt Gate内存布局
	// 	15..00: offset
	// 	31..16: segment selector
	// 	47..32: flags
	// 	63..48: offset
	struct GateDescriptor {
		uint16_t handlerAddressLowBit;
		uint16_t gdt_codeSegmentSelector;
		uint8_t reserved;
		uint8_t access;
		uint16_t handlerAddressHighBit;
	} __attribute__((packed));

	// IDT本体, 其地址要保存到idtr中
	static GateDescriptor interruptDescriptorTable[256];

	struct InterruptDescriptorTablePointer {
		uint16_t size;
		uint32_t base;
	} __attribute__((packed));


	static void SetInterruptDescriptorTableEntry(
		uint8_t interruptNumber,
		uint16_t codeSegmentSelectorOffset,
		void (*handler)(),
		uint8_t DescriptorPrivilegeLevel,
		uint8_t DescriptorType
	);

	// 级联中断控制器(PIC)
	Port8BitSlow picMasterCommand;
	Port8BitSlow picMasterData;
	Port8BitSlow picSlaveCommand;
	Port8BitSlow picSlaveData;


public:
	InterruptManager(GlobalDescriptorTable* gdt);
	~InterruptManager();

	void Activate();

	// 真正处理中断的函数
	static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);

	// 函数本体在interruptstubs.s中
	// 	使用nm命令查看编译后的名称硬编码到
	static void IgnoreInterruptRequest();
	static void HandleInterruptRequest0x00();
	static void HandleInterruptRequest0x01();

};

#endif // !__INTERRUPTS_H
