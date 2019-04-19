#include "MetalDetector.h"

MetalDetector::MetalDetector()
{
	m_pin = METALDETECTOR_PIN;
}

void MetalDetector::init()
{
	pinMode(m_pin, INPUT);
	DEVICESPRINT("MetalDetector.init()");
	//timer.start();
}

void MetalDetector::read(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("MetalDetector.read()");
	/*if (timer.elapsed() > 100)
	{
		Serial.println(analogRead(m_pin));
		timer.start();
	}*/
	if (analogRead(m_pin) > 385) rov_data.m_is_core = 1;
	else rov_data.m_is_core = 0;
}