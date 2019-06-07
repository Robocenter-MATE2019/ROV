#include "DepthSensorMS5837.h"

DepthSensorMS5837::DepthSensorMS5837()
{
}

void DepthSensorMS5837::init()
{
	m_ms5837.init();
	m_ms5837.setModel(MS5837::MS5837_30BA);
	m_ms5837.setFluidDensity(997);
	DEVICESPRINT("DepthSensor.init()");
}

void DepthSensorMS5837::read(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("DepthSensor.read()");
	m_ms5837.read();
	rov_data.m_depth = m_ms5837.pressure();
}