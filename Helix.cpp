#include "Helix.h"

Helix::Helix()
{
	m_helix = LevelMotor(HELIX_MOTOR_LEFT_PIN_ONE, HELIX_MOTOR_RIGHT_PIN_ONE);
	m_helix_ = LevelMotor(HELIX_MOTOR_LEFT_PIN_TWO, HELIX_MOTOR_RIGHT_PIN_TWO);
}

void Helix::init()
{
	m_helix_.init();
	m_helix.init();	
	DEVICESPRINT("Helix.init()");
}

void Helix::write(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("Helix.write()");
	m_helix.set_power(rov_data.m_helix_one);
	m_helix_.set_power(rov_data.m_helix_two);
}