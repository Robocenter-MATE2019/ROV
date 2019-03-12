#include "MetalDetector.h"

MetalDetector::MetalDetector()
{
	m_pin = METALDETECTOR_PIN;
}

void MetalDetector::init()
{
	pinMode(m_pin, INPUT);
}

void MetalDetector::read(RovData& rov_data)
{
	if (analogRead(m_pin) > 512) rov_data.m_is_core = true;
	else rov_data.m_is_core = false;
}