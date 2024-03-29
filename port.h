#ifndef __PORT_H
#define __PORT_H

#include "types.h"

class Port {
protected:
	uint16_t portnumber;
	Port(uint16_t portnumber);
	~Port();
};


// 端口的8bit读写
class Port8Bit: public Port {
public:
	Port8Bit(uint16_t portnumber);
	~Port8Bit();
	virtual void Write(uint8_t data);
	virtual uint8_t Read();
};

class Port8BitSlow: public Port8Bit {
public:
	Port8BitSlow(uint16_t portnumber);
	~Port8BitSlow();
	virtual void Write(uint8_t data);
};

// 端口的16bit读写
class Port16Bit: public Port {
public:
	Port16Bit(uint16_t portnumber);
	~Port16Bit();
	virtual void Write(uint16_t data);
	virtual uint16_t Read();
};

// 端口的32bit读写
class Port32Bit: public Port {
public:
	Port32Bit(uint16_t portnumber);
	~Port32Bit();
	virtual void Write(uint32_t data);
	virtual uint32_t Read();
};

#endif // !__PORT_H

