#include "ThrustersSubSystem.h"

ThrustersSubSystem::ThrustersSubSystem()
{
	m_motors[0] = BrushlessMotor (H_FRONT_LEFT);
	m_motors[1] = BrushlessMotor(H_FRONT_RIGHT);
	m_motors[2] = BrushlessMotor(H_BACK_LEFT);
	m_motors[3] = BrushlessMotor(H_BACK_RIGHT);
	m_motors[4] = BrushlessMotor(V_FRONT_LEFT);
	m_motors[5] = BrushlessMotor(V_FRONT_RIGHT);
	m_motors[6] = BrushlessMotor(V_BACK_LEFT);
	m_motors[7] = BrushlessMotor(V_BACK_RIGHT);

	m_motors[0].set_inverse(H_FRONT_LEFT_INVERSE);
	m_motors[1].set_inverse(H_FRONT_RIGHT_INVERSE);
	m_motors[2].set_inverse(H_BACK_LEFT_INVERSE);
	m_motors[3].set_inverse(H_BACK_RIGHT_INVERSE);
	m_motors[4].set_inverse(V_FRONT_LEFT_INVERSE);
	m_motors[5].set_inverse(V_FRONT_RIGHT_INVERSE);
	m_motors[6].set_inverse(V_BACK_LEFT_INVERSE);
	m_motors[7].set_inverse(V_BACK_RIGHT_INVERSE);

	m_yaw_reg = PIDRegulator(1.3, 100, 1000);
	m_depth_reg = PIDRegulator(1.3, 100, 1000);
	m_roll_reg = PIDRegulator(1.3, 100, 1000);
	m_pitch_reg = PIDRegulator(1.3, 100, 1000);
}

void ThrustersSubSystem::init()
{
	for (auto& motor : m_motors)
	{
		motor.init();
	}
	DEVICESPRINT("ThrustersSubSystem.init()");
}

void ThrustersSubSystem::set_power(int8_t x, int8_t y, int8_t w, int8_t z, uint8_t regulator_type, RovData& rov_data)
{
	int8_t power[THRUSTER_SIZE];
	if (rov_data.m_axis_z == 0)
	{
		//rov_data.m_depth_to_set = ...getDepth();
	}
	if (rov_data.m_axis_w == 0)
	{
		//rov_data.m_yaw_to_set = ...getYaw();
	}
	if (regulator_type & 0x0)
	{
		manual_regulator(power, x, y, w, z);
		pitch_regulator(power, x, y, w, z, rov_data);
		roll_regulator(power, x, y, w, z, rov_data);
	}
	if(regulator_type & 0x1)
	{
		depth_regulator(power, x, y, w, z, rov_data);
	}
	if (regulator_type & 0x2)
	{
		pitch_regulator(power, x, y, w, z, rov_data);
		roll_regulator(power, x, y, w, z, rov_data);
	}
	if (regulator_type & 0x4)
	{
		yaw_regulator(power, x, y, w, z, rov_data);
		depth_regulator(power, x, y, w, z, rov_data);
		pitch_regulator(power, x, y, w, z, rov_data);
		roll_regulator(power, x, y, w, z, rov_data);
	}
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
	power[6] = constrain(z, -100, 100);
	power[7] = constrain(z, -100, 100);
}

void ThrustersSubSystem::yaw_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z, RovData& rov_data)
{
	w = m_yaw_reg.apply(rov_data.m_yaw_to_set, rov_data.m_depth);
	power[0] = constrain(y - x + w, -100, 100);
	power[1] = constrain(y + x - w, -100, 100);
	power[2] = constrain(y - x - w, -100, 100);
	power[3] = constrain(y + x + w, -100, 100);
	power[4] = constrain(z, -100, 100);
	power[5] = constrain(z, -100, 100);
	power[6] = constrain(z, -100, 100);
	power[7] = constrain(z, -100, 100);
}

void ThrustersSubSystem::pitch_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z, RovData& rov_data)
{
	z = m_pitch_reg.apply(rov_data.m_pitch_to_set, rov_data.m_pitch);
	power[0] = constrain(y - x + w, -100, 100);
	power[1] = constrain(y + x - w, -100, 100);
	power[2] = constrain(y - x - w, -100, 100);
	power[3] = constrain(y + x + w, -100, 100);
	power[4] = constrain(z, -100, 100);
	power[5] = constrain(z, -100, 100);
	power[6] = constrain(-z, -100, 100);
	power[7] = constrain(-z, -100, 100);

}

void ThrustersSubSystem::roll_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z, RovData& rov_data)
{
	z = m_roll_reg.apply(rov_data.m_roll_to_set, rov_data.m_roll);
	power[0] = constrain(y - x + w, -100, 100);
	power[1] = constrain(y + x - w, -100, 100);
	power[2] = constrain(y - x - w, -100, 100);
	power[3] = constrain(y + x + w, -100, 100);
	power[4] = constrain(-z, -100, 100);
	power[5] = constrain(z, -100, 100);
	power[6] = constrain(-z, -100, 100);
	power[7] = constrain(z, -100, 100);
}

void ThrustersSubSystem::depth_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z, RovData& rov_data)
{
	z = m_depth_reg.apply(rov_data.m_depth_to_set, rov_data.m_depth);
	power[0] = constrain(y - x + w, -100, 100);
	power[1] = constrain(y + x - w, -100, 100);
	power[2] = constrain(y - x - w, -100, 100);
	power[3] = constrain(y + x + w, -100, 100);
	power[4] = constrain(z, -100, 100);
	power[5] = constrain(z, -100, 100);
	power[6] = constrain(z, -100, 100);
	power[7] = constrain(z, -100, 100);
}

void ThrustersSubSystem::write(RovData& rov_data)
{
	set_power(rov_data.m_axis_x, rov_data.m_axis_y, rov_data.m_axis_w, rov_data.m_axis_z, rov_data.m_regulator_type, rov_data);
	DEVICESPRINT("ThrustersSubSystem.write()");
}
