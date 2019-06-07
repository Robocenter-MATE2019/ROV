#include "ROVBuilderManipulator.h"

ROVBuilderManipulator::ROVBuilderManipulator()
{
	m_rotate_level_motor = LevelMotor(MANIPULATOR_ROTATE_LEFT, MANIPULATOR_ROTATE_RIGHT);
	m_release_level_motor = LevelMotor(MANIPULATOR_RELEASE_LEFT, MANIPULATOR_RELEASE_RIGHT);
}

void ROVBuilderManipulator::init()
{
	m_release_level_motor.init();
	m_rotate_level_motor.init();
	DEVICESPRINT("ROVBuilderManipulator.init()");
}

void ROVBuilderManipulator::set_power(int8_t release, int8_t rotate)
{
	m_release_level_motor.set_power(release);
	m_rotate_level_motor.set_power(rotate);
}

void ROVBuilderManipulator::write(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("ROVBuilderManipulator.write()");
	m_release_level_motor.set_inverse(rov_data.m_manipulator_release_inverse);
	m_rotate_level_motor.set_inverse(rov_data.m_manipulator_rotate_inverse);
	set_power(rov_data.m_manipulator_grab, -rov_data.m_manipulator_rotate);
}
