#pragma once

#include "Input.h"
#include "TemperatureSensor.h"
#include "RovData.h"

class Sensors : public Input
{
public:
	Sensors();
	void init();
	void read(RovData& rov_data);
private:
	TemperatureSensor m_temperature_sensor;
	//IMU m_imu_sensor;
	//DepthSensor m_depth_sensor;
};