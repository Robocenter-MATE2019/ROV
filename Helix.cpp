#include "Helix.h"

Helix::Helix()
{
	m_helix = LevelMotor(HELIX_MOTOR_LEFT_PIN, HELIX_MOTOR_RIGHT_PIN);
}

void Helix::init()
{
	m_helix.init();	
	DEVICESPRINT("Helix.init()");
}

void Helix::write(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("Helix.write()");
	m_helix.set_power(rov_data.m_helix);
	
}