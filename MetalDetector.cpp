#include "MetalDetector.h"

MetalDetector::MetalDetector()
{
	m_pin = METALDETECTOR_PIN;
}

void MetalDetector::init()
{
	pinMode(m_pin, INPUT);
	DEVICESPRINT("MetalDetector.init()");
}

void MetalDetector::read(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("MetalDetector.read()");
	if (analogRead(m_pin) > 385) rov_data.m_is_core = 1;
	else rov_data.m_is_core = 0;
}