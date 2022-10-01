#include "types.h""
void printf(char* str) {
	static uint16_t* VideoMemory = (uint16_t*)0xb8000;

	for(int i=0; str[i]!='\0'; ++i)
		// overwrite hight bit(color bit)
		VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
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

// 不要改名
extern "C" void kernelMain(void* multiboot_struct, uint32_t magicnumber) {
	printf("hi there, hello ring");
	while(1);
}

