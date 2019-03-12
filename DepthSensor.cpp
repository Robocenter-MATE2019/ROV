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
}