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
	if (analogRead(m_pin) > 900) rov_data.m_is_core = true;
	else rov_data.m_is_core = false;
	DEVICESPRINT("MetalDetector.read()");
	TIME_DEBUGER(timer_macros);
}