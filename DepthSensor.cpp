#include "DepthSensor.h"

DepthSensor::DepthSensor() : m_ms5803(ADDRESS_LOW) 
{
}

void DepthSensor::init()
{
	m_ms5803.reset();
	m_ms5803.begin();
	DEVICESPRINT("DepthSensor.init()");
}

void DepthSensor::read(RovData& rov_data)
{
	rov_data.m_depth = m_ms5803.getPressure(ADC_4096);
	DEVICESPRINT("DepthSensor.read()");
#ifdef TIMERS
	if (timer_macros.elapsed() > 1000)
	{
		Serial.println(__FILE__);
		Serial.print("LAG!!! time = ");
		Serial.println(timer_macros.elapsed());
		delay(10000000000000000);
	}
	timer_macros.start();
#endif
}