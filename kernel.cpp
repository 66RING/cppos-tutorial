#include "types.h"
#include "gdt.h"
#include "interrupts.h"


void printf(char* str) {
	static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i) {
        switch(str[i]) {
            case '\n':
                x = 0;
                y++;
                break;
            default:
				// overwrite hight bit(color bit)
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80) {
            x = 0;
            y++;
        }

		// 再多清屏
        if(y >= 25) {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

// 使用pointer as constructor
// constructors都放在 ctors这段里面
typedef void(*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
	for (constructor i = start_ctors; i != end_ctors; i++)
		(*i)();
}

// 不让编译器改名供外部汇编使用
extern "C" void kernelMain(void* multiboot_struct, uint32_t magicnumber) {
	printf("hi there, hello ring");
	GlobalDescriptorTable gdt;
	InterruptManager interrupts(&gdt);

	interrupts.Activate();

	while(1);
}

