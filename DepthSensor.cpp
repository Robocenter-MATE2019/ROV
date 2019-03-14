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
	if (m_timer.elapsed() > 1000)
	{
		Serial.println(__FILE__);
		Serial.print("LAG!!! time = ");
		Serial.println(m_timer.elapsed());
		delay(10000000000000000);
	}
	m_timer.start();
}