#include "ThrustersSubSystem.h"

ThrustersSubSystem::ThrustersSubSystem()
{
	m_motors[0] = BrushlessMotor (H_FRONT_LEFT);
	m_motors[1] = BrushlessMotor(H_FRONT_RIGHT);
	m_motors[2] = BrushlessMotor(H_BACK_LEFT);
	m_motors[3] = BrushlessMotor(H_BACK_RIGHT);
	m_motors[4] = BrushlessMotor(V_LEFT);
	m_motors[5] = BrushlessMotor(V_RIGHT);
	m_motors[0].set_inverse(H_FRONT_LEFT_INVERSE);
	m_motors[1].set_inverse(H_FRONT_RIGHT_INVERSE);
	m_motors[2].set_inverse(H_BACK_LEFT_INVERSE);
	m_motors[3].set_inverse(H_BACK_RIGHT_INVERSE);
	m_motors[4].set_inverse(V_LEFT_INVERSE);
	m_motors[5].set_inverse(V_RIGHT_INVERSE);
}

void ThrustersSubSystem::init()
{
	for (auto& motor : m_motors)
	{
		motor.init();
	}
	DEVICESPRINT("ThrustersSubSystem.init()");
}

void ThrustersSubSystem::set_power(int8_t x, int8_t y, int8_t w, int8_t z, uint8_t regulator_type)
{
	int8_t power[THRUSTER_SIZE];
	if(regulator_type & 0x1)
	{
	}
	if (regulator_type & 0x2)
	{
	}
	if (regulator_type & 0x4)
	{
	}
	manual_regulator(power, x, y, w, z);
	for (int i = 0; i < THRUSTER_SIZE; i++)
	{
		m_motors[i].set_power(power[i]);
	}
}

void ThrustersSubSystem::manual_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z)
{
	power[3] = constrain(y + x + w, -100, 100);
	power[2] = constrain(y - x - w, -100, 100);
	power[0] = constrain(y - x + w, -100, 100);
	power[1] = constrain(y + x - w, -100, 100);
	power[4] = constrain(z, -100, 100);
	power[5] = constrain(z, -100, 100);

}

void ThrustersSubSystem::write(RovData& rov_data)
{
	set_power(rov_data.m_axis_x, rov_data.m_axis_y, rov_data.m_axis_w, rov_data.m_axis_z, rov_data.m_regulator_type);
	DEVICESPRINT("ThrustersSubSystem.write()");
}
