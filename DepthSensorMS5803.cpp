#include "DepthSensorMS5803.h"

DepthSensorMS5803::DepthSensorMS5803() : m_ms5803(ADDRESS_LOW)
{
}

void DepthSensorMS5803::init()
{
	m_ms5803.reset();
	m_ms5803.begin();
	DEVICESPRINT("DepthSensor.init()");
}

void DepthSensorMS5803::read(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("DepthSensor.read()");
	rov_data.m_depth = m_ms5803.getPressure(ADC_4096);
}