#include "Helix.h"

Helix::Helix()
{
	m_left_helix = LevelMotor(LEFT_HELIX_MOTOR_LEFT_PIN, LEFT_HELIX_MOTOR_RIGHT_PIN);
	m_right_helix = LevelMotor(RIGHT_HELIX_MOTOR_LEFT_PIN, RIGHT_HELIX_MOTOR_RIGHT_PIN);
}

void Helix::init()
{
	m_left_helix.init();
	m_right_helix.init();	
	DEVICESPRINT("Helix.init()");
}

void Helix::write(RovData& rov_data)
{
	TIME_DEBUGER;
	m_left_helix.set_power(rov_data.m_left_helix);
	m_right_helix.set_power(rov_data.m_right_helix);
	DEVICESPRINT("Helix.write()");
}