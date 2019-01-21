#pragma once
#include <stdint.h>

struct Axis
{
	int8_t x;
	int8_t y;
	int8_t z;
};

class UARTCommunicator
{
public:
	void init();
	bool read(Axis &axis);
};

