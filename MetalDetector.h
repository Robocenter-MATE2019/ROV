#pragma once

#include "Config.h"
#include "Input.h"
#include "RovData.h"

class MetalDetector : public Input
{
public:
	MetalDetector();
	void init();
	void read(RovData& rov_data);
private:
	uint8_t m_pin;
};