#include "ThrustersSubSystem.h"

ThrustersSubSystem::ThrustersSubSystem()
{
	m_motors[0] = BrushlessMotor(H_FRONT_LEFT);
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

	m_yaw_reg = PIDRegulator(3.14, 0, 5);  //3.14 0.1 10
	m_depth_reg = PIDRegulator(6, 0, 10); //6 0.1 10
	m_roll_reg = PIDRegulator(2.3, 0, 3); //2.3 0.1 3
	m_pitch_reg = PIDRegulator(2.3, 0, 3);//2.3 0.1 3
}

void ThrustersSubSystem::init()
{
	for (auto& motor : m_motors)
	{
		motor.init();
	}
	timer_.start();
	DEVICESPRINT("ThrustersSubSystem.init()");
}

void ThrustersSubSystem::regulator_check(int8_t power[], RovData& rov_data)
{
	if (rov_data.m_axis_z == 0 && !flag_depth)
	{
		rov_data.m_depth_to_set = rov_data.m_depth;
		flag_depth = true;
	}
	else if (rov_data.m_axis_z != 0) flag_depth = false;
	if (rov_data.m_axis_w == 0 && !flag_yaw)
	{
		rov_data.m_yaw_to_set = rov_data.m_yaw;
		flag_yaw = true;
	}
	else if (rov_data.m_axis_w != 0) flag_yaw = false;
	if (rov_data.m_yaw_reg_enable && flag_yaw) applyYawReg(power, rov_data);
	if (rov_data.m_depth_reg_enable && flag_depth) applyDepthReg(power, rov_data);
	if (rov_data.m_pitch_reg_enable) applyPitchReg(power, rov_data);
	if (rov_data.m_roll_reg_enable) applyRollReg(power, rov_data);
}

void ThrustersSubSystem::applyDepthReg(int8_t power[], RovData& rov_data)
{
	int pow = m_depth_reg.apply(rov_data.m_depth_to_set, rov_data.m_depth, true);
	/*int8_t max_ = find_max(power, 4, 7);
	if (max_ + pow >= MAX_POWER)
	{
		power[4] -= MAX_POWER;
		power[5] -= MAX_POWER;
		power[6] -= MAX_POWER;
		power[7] -= MAX_POWER;
	}
	else if (max_ + pow <= -MAX_POWER)
	{
		power[4] += MAX_POWER;
		power[5] += MAX_POWER;
		power[6] += MAX_POWER;
		power[7] += MAX_POWER;
	}*/
	power[4] = constrain(power[4] + pow, -MAX_POWER, MAX_POWER);
	power[5] = constrain(power[5] + pow, -MAX_POWER, MAX_POWER);
	power[6] = constrain(power[6] + pow, -MAX_POWER, MAX_POWER);
	power[7] = constrain(power[7] + pow, -MAX_POWER, MAX_POWER);
}

void ThrustersSubSystem::applyYawReg(int8_t power[], RovData& rov_data)
{
	int pow = m_yaw_reg.apply(rov_data.m_yaw_to_set, rov_data.m_yaw);
	/*int8_t max_ = find_max(power, 0, 3);
	if (max_ + pow >= MAX_POWER)
	{
		power[0] -= MAX_POWER;
		power[1] -= MAX_POWER;
		power[2] -= MAX_POWER;
		power[3] -= MAX_POWER;
	}
	else if (max_ + pow <= -MAX_POWER)
	{
		power[0] += MAX_POWER;
		power[1] += MAX_POWER;
		power[2] += MAX_POWER;
		power[3] += MAX_POWER;
	}*/
	power[0] = constrain(power[0] - pow, -MAX_POWER, MAX_POWER);
	power[1] = constrain(power[1] + pow, -MAX_POWER, MAX_POWER);
	power[2] = constrain(power[2] - pow, -MAX_POWER, MAX_POWER);
	power[3] = constrain(power[3] + pow, -MAX_POWER, MAX_POWER);
	
}

void ThrustersSubSystem::applyRollReg(int8_t power[], RovData& rov_data)
{
	int pow = m_roll_reg.apply(rov_data.m_roll_to_set, rov_data.m_roll);
	/*int8_t max_ = find_max(power, 4, 7);
	if (max_ + pow >= MAX_POWER)
	{
		power[4] -= MAX_POWER;
		power[5] -= MAX_POWER;
		power[6] -= MAX_POWER;
		power[7] -= MAX_POWER;
	}
	else if (max_ + pow <= -MAX_POWER)
	{
		power[4] += MAX_POWER;
		power[5] += MAX_POWER;
		power[6] += MAX_POWER;
		power[7] += MAX_POWER;
	}*/
	power[4] = constrain(power[4] + pow, -MAX_POWER, MAX_POWER);
	power[5] = constrain(power[5] + pow, -MAX_POWER, MAX_POWER);
	power[6] = constrain(power[6] - pow, -MAX_POWER, MAX_POWER);
	power[7] = constrain(power[7] - pow, -MAX_POWER, MAX_POWER);
	
}

void ThrustersSubSystem::applyPitchReg(int8_t power[], RovData& rov_data)
{
	int pow = m_pitch_reg.apply(rov_data.m_pitch_to_set, rov_data.m_pitch);
	int8_t max_ = find_max(power, 4, 7);
	/*if (max_ + pow >= MAX_POWER)
	{
		power[4] -= MAX_POWER;
		power[5] -= MAX_POWER;
		power[6] -= MAX_POWER;
		power[7] -= MAX_POWER;
	}
	else if (max_ + pow <= -MAX_POWER)
	{
		power[4] += MAX_POWER;
		power[5] += MAX_POWER;
		power[6] += MAX_POWER;
		power[7] += MAX_POWER;
	}*/
	power[4] = constrain(power[4] - pow, -MAX_POWER, MAX_POWER);
	power[5] = constrain(power[5] + pow, -MAX_POWER, MAX_POWER);
	power[6] = constrain(power[6] - pow, -MAX_POWER, MAX_POWER);
	power[7] = constrain(power[7] + pow, -MAX_POWER, MAX_POWER);
}

void ThrustersSubSystem::set_power(int8_t x, int8_t y, int8_t w, int8_t z, uint8_t regulator_type, RovData& rov_data)
{
	int8_t power[THRUSTER_SIZE] = {0};
	manual_regulator(power, x, y, w, z);
	regulator_check(power, rov_data);

	for (int i = 0; i < THRUSTER_SIZE; i++)
	{
		m_motors[i].set_power(power[i]);
	}
}

void ThrustersSubSystem::manual_regulator(int8_t power[], int8_t x, int8_t y, int8_t w, int8_t z)
{
	power[0] = constrain(y + x + w, -MAX_POWER, MAX_POWER);
	power[1] = constrain(y - x - w, -MAX_POWER, MAX_POWER);
	power[2] = constrain(y - x + w, -MAX_POWER, MAX_POWER);
	power[3] = constrain(y + x - w, -MAX_POWER, MAX_POWER);
	power[4] = constrain(z, -MAX_POWER, MAX_POWER);
	power[5] = constrain(z, -MAX_POWER, MAX_POWER);
	power[6] = constrain(z, -MAX_POWER, MAX_POWER);
	power[7] = constrain(z, -MAX_POWER, MAX_POWER);
}

void ThrustersSubSystem::write(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("ThrustersSubSystem.write()");
	set_power(rov_data.m_axis_x, rov_data.m_axis_y, rov_data.m_axis_w, rov_data.m_axis_z, rov_data.m_regulator_type, rov_data);
}

int8_t ThrustersSubSystem::find_max(int8_t power[], int8_t first, int8_t last)
{
	int8_t max = 0;
	for (int8_t i = first; i <= last; i++)
	{
		if (power[i] > max) max = power[i];
	}
	return max;
}

//void ThrustersSubSystem::goat_feature(int8_t power[], RovData& rov_data)
//{
//	rov_data.m_roll = rov_data.m_yaw;
//	applyRollReg(power, rov_data);
//}

//void ThrustersSubSystem::flip_feature()
//{
//	m_motors[4].set_inverse(!m_motors[4].get_inverse);
//	m_motors[5].set_inverse(!m_motors[5].get_inverse);
//}