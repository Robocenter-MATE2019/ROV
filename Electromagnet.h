#pragma once

#include "Config.h"
#include "RovData.h"
#include "Output.h"

class Electromagnet : public Output
{
public:
	Electromagnet();
	void init();
	void write(RovData& rov_data);
private:
	uint8_t m_pin;
};