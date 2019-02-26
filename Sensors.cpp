#include "Sensors.h"

Sensors::Sensors()
{
	m_temperature_sensor = TemperatureSensor(TEMPERATURE_SENSOR);
	//m_imu_sensor = IMU(IMU_SENSOR);
	//m_depth_sensor = DepthSensor(DEPTH_SENSOR);
}

void Sensors::init()
{
	
}

void Sensors::read(RovData& rov_data)
{
	//rov_data.m_pitch = m_imu_sensor.getPitch();
	//rov_data.m_roll = m_imu_sensor.getRoll();
	//rov_data.m_yaw = m_imu_sensor.getYaw();
	//rov_data.m_depth = m_depth_sensor.getDepth();
	rov_data.m_temperature = m_temperature_sensor.getTemperature();
}