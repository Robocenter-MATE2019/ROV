#include "Coiler.h"

Coiler::Coiler()
{
	m_coil_motor = LevelMotor(COIL_MOTOR_LEFT_PIN, COIL_MOTOR_LEFT_PIN);
}

void Coiler::init()
{
	m_coil_motor.init();
}

void Coiler::write(RovData& rov_data)
{
	m_coil_motor.set_power(rov_data.m_coiler);
}